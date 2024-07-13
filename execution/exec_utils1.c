/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:10:09 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/22 12:38:43 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_cmd_(char *s, t_list *lst)
{
	char	**path;
	char	*cmd;
	int		i;

	if (access(s, F_OK) == 0)
		return (ft_strdup(s));
	i = 0;
	if (s && s[0] == '\0')
		return (ft_printf("minishell: %s: command not found\n", s), NULL);
	path = ft_split(get_env_value(lst, "PATH"), ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		cmd = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(cmd, s);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		else
			free(cmd);
		i++;
	}
	ft_printf("minishell: %s: command not found\n", s);
	return (NULL);
}

char	*get_path(char *s)
{
	char	*path;

	path = path_cmd_(s, *g_global.lst_env);
	if (!path)
		exit(127);
	return (path);
}
