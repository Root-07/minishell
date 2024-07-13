/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:29:56 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/22 15:30:09 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_is_valid(t_list *lst, char *name)
{
	char	*env;

	env = get_env_value(lst, name);
	if (env)
		return (1);
	return (0);
}

void	exec_exit_supp(char c, char *str)
{
	if (!ft_isdigit(c))
	{
		printf("exit\n");
		ft_printf("minishell: exit: %s: numeric argument required\n", str);
		exit(255);
	}
}

int	exec_exit(char **arr)
{
	int	i;
	int	j;
	int	n;

	j = ((i = 1), 0);
	if (!arr[i])
	{
		printf("exit\n");
		exit(0);
	}
	while (arr[i][j])
	{
		exec_exit_supp(arr[i][j], arr[i]);
		j++;
	}
	i++;
	if (arr[i])
		return (ft_printf("minishell: exit: too many arguments\n"), 1);
	else
	{
		n = ft_atoi(arr[--i]);
		printf("exit\n");
		exit(n);
	}
	return (0);
}

char	**arr_of_env(void)
{
	t_list	*lst;
	t_env	*env;
	char	**arr;
	int		i;

	lst = *g_global.lst_env;
	arr = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (lst)
	{
		env = lst->content;
		arr[i] = ft_strjoin(arr[i], env->name);
		arr[i] = ft_strjoin(arr[i], "=");
		arr[i] = ft_strjoin(arr[i], env->value);
		i++;
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}

int	builtins(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->args[0], "env", 3) && ft_strlen(cmd->args[0]) == 3)
		return (exec_env(*cmd, g_global.lst_env));
	else if (!ft_strncmp(cmd->args[0], "export", 6)
		&& ft_strlen(cmd->args[0]) == 6)
		return (exec_export(*cmd, g_global.lst_env));
	else if (!ft_strncmp(cmd->args[0], "unset", 5)
		&& ft_strlen(cmd->args[0]) == 5)
		return (exec_unset(*cmd, g_global.lst_env));
	else if (!ft_strncmp(cmd->args[0], "echo", 4)
		&& ft_strlen(cmd->args[0]) == 4)
		return (exec_echo((*cmd).args + 1));
	else if (!ft_strncmp(cmd->args[0], "exit", 4)
		&& ft_strlen(cmd->args[0]) == 4)
		return (exec_exit(cmd->args));
	else if (!ft_strncmp(cmd->args[0], "pwd", 3)
		&& ft_strlen(cmd->args[0]) == 3)
		return (exec_pwd(*g_global.lst_env));
	else if (!ft_strncmp(cmd->args[0], "cd", 2) && ft_strlen(cmd->args[0]) == 2)
		return (exec_cd(*cmd, *g_global.lst_env));
	return (0);
}
