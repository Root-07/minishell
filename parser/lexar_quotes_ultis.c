/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_quotes_ultis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 09:58:26 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/18 14:32:42 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_chardup(char c)
{
	char	*str;

	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	check_if_quotes(char *str, int i, int *quotes)
{
	if (*quotes != 0)
	{
		if (str[i] == '\'' && *quotes == SINGLE_QUOTES)
		{
			*quotes = 0;
			if (str[i + 1] == '\0' || str[i + 1] == ' ' || str[i + 1] == '\t')
				return (1);
		}
		else if (str[i] == '\"' && *quotes == DOUBLE_QUOTES)
		{
			*quotes = 0;
			if (str[i + 1] == '\0' || str[i + 1] == ' ' || str[i + 1] == '\t')
				return (1);
		}
	}
	else if (*quotes == 0)
	{
		if (str[i] == '\'')
			*quotes = SINGLE_QUOTES;
		else if (str[i] == '\"')
			*quotes = DOUBLE_QUOTES;
	}
	return (0);
}
