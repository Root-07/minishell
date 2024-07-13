/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_ultis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 09:55:03 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/21 22:00:49 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error_supp(t_list *node)
{
	if (ft_strlen(node->next->content) == 1)
	{
		ft_printf("minishell: syntax error near unexpected token `%c'\n",
			((char *)node->next->content)[0]);
		return (1);
	}
	else if (ft_strlen(node->next->content) > 1)
	{
		ft_printf("minishell: syntax error near unexpected token `%c%c'\n",
			((char *)node->next->content)[0],
			((char *)node->next->content)[0]);
		return (1);
	}
	return (0);
}

int	syntax_error(t_list *node)
{
	if (check_pipe(node->content, 0) == -1 || rdr_error(node->content))
		return (1);
	else if (check_rdr(node->content) && node->next == NULL)
	{
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	else if (check_pipe(node->content, 0) && node->next == NULL)
	{
		ft_printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	else if (check_rdr(node->content) && check_rdr(node->next->content))
	{
		if (syntax_error_supp(node))
			return (1);
	}
	else if (check_rdr(node->content) && check_pipe(node->next->content, -1))
	{
		ft_printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}
