/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:10:03 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/22 12:57:17 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_echo_supp(char *str, int *check)
{
	int	j;
	int	s_check;

	s_check = 0;
	if (str[0] == '-' && str[1])
	{
		j = 1;
		while (str[j])
		{
			if (str[j] != 'n')
			{
				s_check = 1;
				return (1);
			}
			j++;
			if (!str[j])
				*check = 0;
		}
		if (s_check)
			return (1);
	}
	else
		return (1);
	return (0);
}

int	exec_echo(char **args)
{
	int	i;
	int	check;

	check = 1;
	i = 0;
	while (args[i])
	{
		if (exec_echo_supp(args[i], &check))
			break ;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (check)
		printf("\n");
	return (0);
}

int	exec_cd(t_cmd cmd, t_list *list_env)
{
	char	*home;

	home = get_env_value(list_env, "HOME");
	if (cmd.args[1] == NULL)
	{
		if (home == NULL)
		{
			printf("cd : Unable to retrieve home directory\n");
			return (1);
		}
		if (chdir(home) != 0)
		{
			printf("bash: cd: %s: No such file or directory\n", cmd.args[0]);
			return (1);
		}
	}
	else
	{
		if (chdir(cmd.args[1]) != 0)
		{
			printf("bash: cd: %s: No such file or directory\n", cmd.args[1]);
			return (1);
		}
	}
	return (0);
}

int	exec_pwd(t_list *env)
{
	char	*buff;

	buff = NULL;
	(void)env;
	buff = getcwd(buff, PATH_MAX + 1);
	printf("%s\n", buff);
	free(buff);
	return (0);
}
