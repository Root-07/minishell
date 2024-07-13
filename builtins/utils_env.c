/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:25:14 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/21 13:04:52 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_list *lst, char *name)
{
	t_list	*node;
	t_env	*env;

	node = lst;
	if (!name)
		return (NULL);
	while (node)
	{
		env = (t_env *)node->content;
		if (ft_strlen(name) == ft_strlen(env->name))
		{
			if (ft_strncmp(env->name, name, ft_strlen(name)) == 0)
				return (env->value);
		}
		node = node->next;
	}
	return (NULL);
}

void	add_var_to_env(t_list **lst, char *old_str)
{
	char	*str;
	t_env	*env;

	str = check_cmd(old_str);
	env = get_line_of_env(lst, str);
	if (env)
		ft_lstadd_back(lst, ft_lstnew(env));
	free(str);
}

void	print_env(t_list *lst)
{
	t_list	*node;
	t_env	*env;

	node = lst;
	while (node)
	{
		env = node->content;
		printf("%s=%s\n", env->name, env->value);
		node = node->next;
	}
}

void	free_env(void *ptr)
{
	t_env	*env;

	env = ptr;
	free(env->name);
	free(env->value);
	free(env);
}
