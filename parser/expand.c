/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:24:00 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/22 12:30:42 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_expand(t_list **lst, char *line, int *qoutes)
{
	char	*name;
	char	*env;
	int		i;

	name = ((env = NULL), NULL);
	i = 0;
	if (!*line)
	{
		ft_lstadd_back(lst, ft_lstnew(ft_strdup("$")));
		i = 0;
	}
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
	{
		find_quotes(line, i, qoutes);
		i++;
	}
	name = ft_substr(line, 0, i);
	if (name)
	{
		env = get_env_value(*g_global.lst_env, name);
		free(name);
	}
	if (env)
		write_expand(lst, env, qoutes);
	return (i);
}

int	handle_single_qoutes(t_list **lst, char *line, int *qoutes)
{
	char	*env;
	int		i;

	env = NULL;
	i = 1;
	while (line[i] && line[i] != '\'')
	{
		find_quotes(line, i, qoutes);
		i++;
	}
	if (line[i] == '\'')
		i++;
	env = ft_substr(line, 0, i);
	if (env)
		ft_lstadd_back(lst, ft_lstnew(env));
	return (i);
}

int	handel_default(t_list **lst, char *line, int *qoutes)
{
	char	*env;
	char	c;
	int		i;

	env = NULL;
	i = 0;
	while (line[i] && line[i] != '$')
	{
		find_quotes(line, i, qoutes);
		i++;
	}
	env = ft_substr(line, 0, i);
	if (env)
		ft_lstadd_back(lst, ft_lstnew(env));
	if (i == 0)
	{
		c = line[i];
		ft_lstadd_back(lst, ft_lstnew(ft_chardup(c)));
		i++;
	}
	return (i);
}

t_list	*write_expantion_on_lst(char *str)
{
	int		qoutes;
	int		i;
	char	*line;
	t_list	*lst;

	qoutes = ((line = str), (lst = NULL), 0);
	while (line && *line)
	{
		i = 0;
		if (*line == '$' && qoutes != SINGLE_QUOTES)
		{
			i = first_handle(&lst, line + i, &qoutes);
			if (i == 1 && line[i + 1] && !ft_isdigit(line[i + 1]))
			{
				line++;
				i = get_expand(&lst, line, &qoutes);
			}
		}
		else if (*line == '\'')
			i = handle_single_qoutes(&lst, line, &qoutes);
		else
			i = handel_default(&lst, line + i, &qoutes);
		line = line + i;
	}
	return (lst);
}

void	expand(t_cmd **list)
{
	char	c;
	void	*ptr;
	t_list	*command;
	t_list	*node;

	c = 1;
	command = NULL;
	node = NULL;
	command = join_arr_to_lst((*list)->args);
	if (!command)
		return ;
	node = command;
	while (node)
	{
		ptr = node->content;
		node->content = expantion(node->content, 1);
		free(ptr);
		node = node->next;
	}
	(*list)->args = join_lst_to_arr(command);
}
