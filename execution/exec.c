/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:04:22 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/22 15:14:24 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_pipes(int *pipes, int fd)
{
	close(fd);
	if (pipes == NULL)
		return ;
	if (pipes[0] != -1)
		dup2(pipes[0], 0);
	if (pipes[1] != -1)
		dup2(pipes[1], 1);
	close(pipes[0]);
	close(pipes[1]);
}

int	exec_one_cmd(t_cmd *cmd, int *pipes, int fd, int must_fork)
{
	char	*path;
	int		pid;

	expand(&cmd);
	if (!cmd->args)
		return (0);
	if (!cmd->args[0])
		return (0);
	if (is_builtins(cmd->args[0]) && must_fork == 0)
		return (exec_builtin(&cmd[0]));
	pid = fork();
	g_global.is_fork = 1;
	if (pid)
		return (pid);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->outred)
		exit (1);
	handle_pipes(pipes, fd);
	setup_red_(cmd);
	if (is_builtins(cmd->args[0]))
		exit(builtins(cmd));
	path = get_path(cmd[0].args[0]);
	execve(path, cmd->args, arr_of_env());
	return (exit(1), 1);
}

void	cases_of_exec(int *fd, int *p, int *fds, int check)
{
	if (check == 1)
	{
		p[0] = -1;
		p[1] = fds[1];
		*fd = fds[0];
	}
	else if (check == 2)
	{
		p[0] = *fd;
		p[1] = -1;
		*fd = -1;
	}
	else if (check == 3)
	{
		p[0] = *fd;
		p[1] = fds[1];
		*fd = fds[0];
	}
}

int	exec_multiple_cmds(t_cmd *cmd, int cmd_count)
{
	int	fds[2];
	int	p[3];
	int	fd;
	int	i;
	int	pid;

	i = -1;
	while (++i < cmd_count)
	{
		if (i != cmd_count - 1)
			pipe(fds);
		if (i == 0)
			cases_of_exec(&fd, p, fds, 1);
		else if (i == cmd_count -1)
			cases_of_exec(&fd, p, fds, 2);
		else
			cases_of_exec(&fd, p, fds, 3);
		pid = exec_one_cmd(&cmd[i], p, fd, 1);
		close(p[0]);
		close(p[1]);
	}
	return (pid);
}

void	execute(t_cmd *cmd)
{
	int	pid;
	int	cmd_count;
	int	stts;

	pid = 0;
	cmd_count = cmd[0].cmd_len;
	if (cmd_count == 1)
	{
		pid = exec_one_cmd(cmd, NULL, -1, 0);
		signal(SIGQUIT, SIG_IGN);
		if (pid > 0)
		{
			stts = get_exit_status(pid);
			g_global.is_fork = 0;
			set_last_status(stts);
		}
		return ;
	}
	else
	{
		pid = exec_multiple_cmds(cmd, cmd_count);
		set_last_status(get_exit_status(pid));
		while (waitpid(-1, &stts, 0) != -1)
			;
	}
}
