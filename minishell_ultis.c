/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ultis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 05:10:43 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/22 15:09:38 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del(void *data)
{
	free(data);
}

void	no_free(void *ptr)
{
	(void)ptr;
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free_cmd(t_cmd *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = cmd[0].cmd_len;
	while (i < len)
	{
		ft_free_split(cmd[i].args);
		i++;
	}
	free(cmd);
}

void	ft_free_env(void *data)
{
	t_env	*env;

	env = data;
	free(env->name);
	free(env->value);
	free(env);
}
