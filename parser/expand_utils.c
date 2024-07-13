/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:05:27 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/22 12:30:47 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	first_handle(t_list **lst, char *line, int *qoutes)
{
	int	i;

	i = 0;
	if (line[i + 1] && line[i + 1] == '?')
		return (ft_lstadd_back(lst, ft_lstnew(ft_itoa(g_global.status))), 2);
	while (line[i] && line[i] == '$')
	{
		find_quotes(line, i, qoutes);
		i++;
	}
	if (line[i] && line[i] == '"')
	{
		ft_lstadd_back(lst, ft_lstnew(ft_chardup('$')));
		i = 0;
	}
	else if ((i > 1 || (i == 1 && !line[i + 1])) && (i % 2) != 0)
	{
		if (i == 1 && !line[i + 1])
			ft_lstadd_back(lst, ft_lstnew(ft_strdup("$")));
		else if (i > 1)
			return (i - 1);
	}
	return (i);
}

void	write_expand_supp(t_list **lst, char *str, int check)
{
	char	c;

	c = 1;
	ft_lstadd_back(lst, ft_lstnew(ft_strdup(str)));
	if (check)
		ft_lstadd_back(lst, ft_lstnew(ft_chardup(c)));
}

void	write_expand(t_list **lst, char *env, int *qoutes)
{
	char	**arr;
	int		j;

	j = 0;
	if (*qoutes == 0)
	{
		j = 0;
		arr = ft_split(env, ' ');
		if (arr)
		{
			while (arr[j])
			{
				if (arr[j + 1])
					write_expand_supp(lst, arr[j], 1);
				else
					write_expand_supp(lst, arr[j], 0);
				j++;
			}
			ft_free_split(arr);
		}
	}
	else
		write_expand_supp(lst, env, 0);
}
