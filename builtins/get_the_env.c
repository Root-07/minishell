/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:30:22 by ael-amin          #+#    #+#             */
/*   Updated: 2023/06/22 12:26:25 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*get_line_of_env_supp(t_list **lst, char *str, int i, t_env *env)
{
	if (str[i] && str[i] == '=' && !str[i + 1])
	{
		env->value = ft_strdup("\0");
		if (!env->value)
			return (NULL);
	}
	else
	{
		while (*str && *str != '=')
			str++;
		if (*str && *str == '=')
			str++;
		if (*str)
		{
			env->value = ft_substr(str, 0, ft_strlen(str));
			if (!env->value)
				return (NULL);
		}
	}
	if (get_env_value(*lst, env->name))
		unset_env(lst, env->name);
	return (env);
}

t_env	*get_line_of_env(t_list **lst, char *line)
{
	int		i;
	t_env	*env;
	char	*str;

	i = ((str = line), 0);
	env = malloc(sizeof(t_env));
	if (str[i] && (ft_isdigit(str[i]) || str[i] == '='))
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n", str);
		return (g_global.status = 1, NULL);
	}
	while (str[i] && str[i] != '=')
		i++;
	env->name = ft_substr(str, 0, i);
	if (!env->name)
		return (NULL);
	return (get_line_of_env_supp(lst, str, i, env));
}

t_list	*get_env(t_list **lst, char **str)
{
	t_list	*lst_env;
	int		i;

	i = 0;
	while (str[i])
	{
		ft_lstadd_back(&lst_env, ft_lstnew(get_line_of_env(lst, str[i])));
		i++;
	}
	return (lst_env);
}

void	unset_env_supp(t_list **lst, t_env *env, char *name)
{
	t_list	*node;
	t_list	*next;
	t_list	*prive;

	node = *lst;
	prive = node;
	while (node)
	{
		env = node->content;
		next = node->next;
		if (ft_strncmp(env->name, name, ft_strlen(env->name)) == 0
			&& ft_strlen(env->name) == ft_strlen(name))
		{
			prive->next = node->next;
			ft_lstdelone(node, free_env);
		}
		else
			prive = node;
		node = next;
	}
}

int	unset_env(t_list **lst, char *name)
{
	t_list	*node;
	t_env	*env;

	node = *lst;
	env = node->content;
	if (name && name[0] && ft_isdigit(name[0]))
	{
		ft_printf("minishell: unset: `%s': not a valid identifier\n", name);
		return (1);
	}
	if (ft_strncmp(env->name, name, ft_strlen(env->name)) == 0
		&& ft_strlen(env->name) == ft_strlen(name))
	{
		*lst = node->next;
		ft_lstdelone(node, free_env);
		return (0);
	}
	unset_env_supp(lst, env, name);
	return (0);
}
