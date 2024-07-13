/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:10:47 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/22 15:34:14 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(void)
{
	char	*prompt;
	char	*line;

	prompt = ft_strdup("minishell$ ");
	line = readline(prompt);
	if (line == NULL)
	{
		free (prompt);
		return (NULL);
	}
	while (line[0] == '\0')
	{
		free (line);
		line = readline(prompt);
		if (line == NULL)
		{
			free (prompt);
			return (NULL);
		}
	}
	free (prompt);
	return (line);
}

void	handler(int sig)
{
	(void)sig;
	printf("\n");
	if (g_global.is_fork == 1)
	{
		g_global.status = 130;
		g_global.is_fork = 0;
		return ;
	}
	if (g_global.herdoc == -1)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.status = 1;
	}
	else if (g_global.herdoc != -1)
	{
		close(g_global.herdoc);
		g_global.herdoc = -1;
		g_global.status = 0;
	}
}

void	main_utils(t_list **list, t_cmd **cmd, char *line)
{
	add_history(line);
	split_cmd(line, list);
	free(line);
	if (*list)
	{
		if (!check_node(*list))
		{
			*cmd = parser(*list);
			if (*cmd)
			{
				execute(*cmd);
				ft_free_cmd(*cmd);
			}
			ft_lstclear(list, ft_del);
		}
		else
			g_global.status = 258;
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_list	*list;
	t_cmd	*cmd;
	t_list	*lst_env;

	g_global.cmd = -1;
	g_global.herdoc = -1;
	g_global.status = 0;
	av += ac;
	lst_env = get_env(&lst_env, env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
	g_global.lst_env = &lst_env;
	line = get_line();
	while (line)
	{
		list = NULL;
		main_utils(&list, &cmd, line);
		line = get_line();
	}
	ft_lstclear(&lst_env, &ft_free_env);
	ft_lstclear(&g_global.lst_export, &ft_free_env);
	return (0);
}
