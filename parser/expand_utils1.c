/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:07:14 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/22 10:52:06 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expantion(char *str, int check)
{
	t_list	*node;
	t_list	*lst;
	char	*arg;
	char	*cmd;

	node = write_expantion_on_lst(str);
	lst = node;
	arg = ((cmd = NULL), NULL);
	while (lst)
	{
		arg = ft_strjoin(arg, lst->content);
		lst = lst->next;
	}
	ft_lstclear(&node, ft_del);
	if (check)
	{
		cmd = check_cmd(arg);
		free(arg);
		return (cmd);
	}
	return (arg);
}

t_list	*join_arr_to_lst(char **args)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = NULL;
	if (!args || !*args)
		return (NULL);
	while (args[i])
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(args[i])));
		i++;
	}
	ft_free_split(args);
	return (lst);
}

char	**join_lst_to_arr_supp(t_list *lst)
{
	char	**arr;
	int		len;
	int		i;
	t_list	*node;

	node = lst;
	len = ft_lstsize(node);
	arr = (char **)malloc(sizeof(char *) * len + 1);
	i = 0;
	while (i < len)
	{
		arr[i] = ft_strdup(node->content);
		i++;
		node = node->next;
	}
	arr[i] = NULL;
	ft_lstclear(&lst, ft_del);
	return (arr);
}

char	**join_lst_to_arr(t_list *lst)
{
	t_list	*new;
	char	**tmp;
	t_list	*node;
	char	c;
	int		i;

	new = NULL;
	node = lst;
	while (node)
	{
		c = 1;
		if (ft_strchr(node->content, c))
		{
			tmp = ft_split(node->content, c);
			i = -1;
			while (tmp[++i])
				ft_lstadd_back(&new, ft_lstnew(ft_strdup(tmp[i])));
			ft_free_split(tmp);
		}
		else
			ft_lstadd_back(&new, ft_lstnew(ft_strdup(node->content)));
		node = node->next;
	}
	ft_lstclear(&lst, ft_del);
	return (join_lst_to_arr_supp(new));
}
