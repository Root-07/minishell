/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:45:45 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/22 12:30:37 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	herdoc_supp(char *herdoc, int fd, int expand)
{
	char	*str;

	str = herdoc;
	if (expand == 0)
		ft_putstr_fd(herdoc, fd);
	else if (expand == 1)
		write_expantion(str, fd);
}

char	*get_herdoc(int fd)
{
	char	*str;
	char	*herdoc;

	str = get_next_line(fd);
	if (str && str[0] == '\n' && !str[1])
		str[0] = '\0';
	else
	{
		herdoc = ft_strtrim(str, "\n");
		free(str);
		return (herdoc);
	}
	return (str);
}

int	herdoc(char *file, int expand)
{
	int		fd[2];
	char	*herdoc;
	int		input;

	pipe(fd);
	input = dup(0);
	g_global.herdoc = input;
	herdoc = get_herdoc(input);
	while (herdoc)
	{
		if (ft_strncmp(herdoc, file, ft_strlen(file)) == 0
			&& ft_strlen(herdoc) == ft_strlen(file))
			break ;
		else
		{
			herdoc_supp(herdoc, fd[1], expand);
			ft_putstr_fd("\n", fd[1]);
		}
		free(herdoc);
		herdoc = get_herdoc(input);
	}
	if (herdoc)
		free(herdoc);
	return (close(fd[1]), fd[0]);
}

int	is_expand(char *str)
{
	if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		return (0);
	return (1);
}

int	read_herdocs(t_list *node)
{
	int		fd;
	int		expand;
	char	*file;

	fd = -1;
	while (node && node->next && !check_pipe(node->content, 0))
	{
		if (check_rdr(node->content) == RDR_HERDOC)
		{
			node = node->next;
			expand = is_expand(node->content);
			file = check_cmd(node->content);
			if (file)
			{
				close(fd);
				fd = herdoc(file, expand);
				if (g_global.herdoc == -2)
					break ;
				free(file);
			}
		}
		node = node->next;
	}
	return (fd);
}
