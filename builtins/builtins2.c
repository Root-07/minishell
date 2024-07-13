/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:20:59 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/22 12:30:08 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_env(t_cmd cmd, t_list **lst_env)
{
	if (cmd.args[1] != NULL)
	{
		ft_printf("env: %s: No such file or directory\n", cmd.args[1]);
		return (127);
	}
	else
		print_env(*lst_env);
	return (0);
}

void	print_export(void)
{
	t_list	*lst;
	t_env	*env;

	lst = *(g_global.lst_env);
	while (lst)
	{
		env = lst->content;
		printf("declare -x ");
		printf("%s=\"%s\"\n", env->name, env->value);
		lst = lst->next;
	}
	lst = g_global.lst_export;
	while (lst)
	{
		printf("declare -x ");
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}

int	exec_export(t_cmd cmd, t_list **lst_env)
{
	int	i;

	i = 1;
	if (cmd.args[1] == NULL)
		print_export();
	while (cmd.args[i])
	{
		if (ft_strchr(cmd.args[i], '='))
			add_var_to_env(lst_env, cmd.args[i]);
		else
			ft_lstadd_back(&g_global.lst_export,
				ft_lstnew(ft_strdup(cmd.args[i])));
		i++;
	}
	return (0);
}

int	exec_unset(t_cmd cmd, t_list **lst_env)
{
	int	i;
	int	len;

	i = 1;
	while (cmd.args[i])
	{
		len = unset_env(lst_env, cmd.args[i]);
		i++;
	}
	return (len);
}
