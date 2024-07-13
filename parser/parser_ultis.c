/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ultis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:35:31 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/21 22:05:04 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_cmd_line(t_list *list)
{
	t_list	*node;
	int		len;

	len = 0;
	node = list;
	while (node != NULL)
	{
		if (!ft_strncmp((char *)node->content, "|", 1)
			&& ft_strlen((char *)node->content) == 1)
			len++;
		node = node->next;
	}
	return (len + 1);
}

void	get_arrgs_supp(t_list *node, t_cmd *cmd, int len, int cmd_len)
{
	int	i;

	i = 0;
	cmd->args = malloc(sizeof(char *) * (len + 1));
	while (node && i < len && !check_pipe(node->content, 0))
	{
		if (node->next != NULL && check_rdr(node->content) != 0)
			node = node->next->next;
		if (!node)
			break ;
		if (node && !check_pipe(node->content, 0) && !check_rdr(node->content))
		{
			cmd->args[i] = ft_strdup(node->content);
			i++;
			node = node->next;
		}
	}
	cmd->args[i] = NULL;
	cmd->ifd = NONE;
	cmd->ofd = NONE;
	cmd->inred = NONE;
	cmd->outred = NONE;
	cmd->herdoc = NONE;
	cmd->first_rdr = NONE;
	cmd->cmd_len = cmd_len;
}

t_cmd	get_args(t_list *lst, int cmd_len)
{
	t_cmd	cmd;
	t_list	*node;
	int		len;
	int		i;

	node = lst;
	len = 0;
	i = 0;
	cmd.outred = 0;
	while (node && !check_pipe(node->content, 0))
	{
		if (node->next && check_rdr(node->content) != 0)
			node = node->next->next;
		if (!node)
			break ;
		if (check_pipe(node->content, 0))
			break ;
		if (node && !check_rdr(node->content))
		{
			len++;
			node = node->next;
		}
	}
	get_arrgs_supp(lst, &cmd, len, cmd_len);
	return (cmd);
}

int	check_onbiges(char *file)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = 0;
	c = 1;
	while (file[i])
	{
		if (file[i] == c)
			len++;
		i++;
	}
	if (len > 0)
		return (1);
	return (0);
}
