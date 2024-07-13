/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:48:48 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/22 13:14:49 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_expantion(char *herdoc, int fd)
{
	char	*line;

	line = expantion(herdoc, 0);
	if (line)
	{
		ft_putstr_fd(line, fd);
		free(line);
	}
}

t_cmd	*parser(t_list *node)
{
	t_cmd	*cmd;
	int		len;
	int		rdr;
	int		i;

	len = get_cmd_line(node);
	cmd = malloc(sizeof(t_cmd) * len);
	i = -1;
	while (node && ++i < len)
	{
		cmd[i] = get_args(node, len);
		cmd[i].herdoc = read_herdocs(node);
		while (node && node->next && !check_pipe(node->content, 0))
		{
			rdr = check_rdr(node->content);
			if (rdr != 0)
				node = node->next;
			if (rdr != 0 && redirections(&cmd[i], node->content, rdr))
				return (ft_free_cmd(cmd), NULL);
			node = node->next;
		}
		if (node)
			node = node->next;
	}
	return (cmd);
}
