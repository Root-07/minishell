/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:27:43 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/22 12:16:15 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_red_(t_cmd *node)
{
	if (node->ofd != 0)
	{
		dup2(node->ofd, STDIN_FILENO);
		close(node->ofd);
	}
	if (node->ifd != 0)
	{
		dup2(node->ifd, STDOUT_FILENO);
		close(node->ifd);
	}
	if (node->inred != 0)
	{
		dup2(node->inred, STDOUT_FILENO);
		close(node->inred);
	}
	if (node->herdoc != 0)
	{
		dup2(node->herdoc, STDIN_FILENO);
		close(node->herdoc);
	}
}

int	exec_builtin(t_cmd *cmd)
{
	int	ret;
	int	fds[2];

	if (cmd->outred)
	{
		set_last_status(1);
		return (1);
	}
	fds[0] = dup(0);
	fds[1] = dup(1);
	setup_red_(cmd);
	ret = builtins(cmd);
	dup2(fds[0], 0);
	dup2(fds[1], 1);
	close(fds[0]);
	close(fds[1]);
	set_last_status(ret);
	return (-1);
}

int	is_builtins(char *cmd)
{
	if (!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
		return (1);
	else if (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
		return (1);
	else if (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
		return (1);
	else if (!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
		return (1);
	else if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
		return (1);
	else if (!ft_strncmp(cmd, "cd", 2) && ft_strlen(cmd) == 2)
		return (1);
	return (0);
}
