/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:02:51 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/21 22:04:56 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quotes_error(int type)
{
	if (type)
		printf("minishell: missing the single or double quotes.\n");
	else
		printf("minishell: : command not found\n");
	exit(1);
}

void	check_quotes_supp(char *input, int *i, int *quotes)
{
	if (input[*i] == '\'')
	{
		if (*quotes == SINGLE_QUOTES)
			*quotes = 0;
		else if (*quotes == 0)
			*quotes = SINGLE_QUOTES;
	}
	else if (input[*i] == '\"')
	{
		if (*quotes == DOUBLE_QUOTES)
			*quotes = 0;
		else if (*quotes == 0)
			*quotes = DOUBLE_QUOTES;
	}
}

int	check_quotes(char *input)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (input[i] != '\0' && (input[i] == ' ' || input[i] == '\t'))
		i++;
	while (input[i] != '\0')
	{
		check_quotes_supp(input, &i, &quotes);
		i++;
	}
	if (quotes == 0)
		return (0);
	ft_printf("minishell: missing the single or double quotes.\n");
	return (1);
}

int	find_qoutes_supp(char *str, int i, int *quotes)
{
	if (*quotes == 0)
		*quotes = DOUBLE_QUOTES;
	else if (*quotes == DOUBLE_QUOTES)
	{
		*quotes = 0;
		return (0);
	}
	while (str[i++] != '\0')
	{
		if (str[i] == '\"' && *quotes == DOUBLE_QUOTES)
			return (0);
	}
	return (1);
}

int	find_quotes(char *str, int i, int *quotes)
{
	if (str[i] == '\'')
	{
		if (*quotes == 0)
			*quotes = SINGLE_QUOTES;
		else if (*quotes == SINGLE_QUOTES)
		{
			*quotes = 0;
			return (0);
		}
		else if (*quotes == DOUBLE_QUOTES)
			return (1);
		while (str[i++] != '\0')
		{
			if (str[i] == '\'' && *quotes == SINGLE_QUOTES)
				return (0);
		}
	}
	else if (str[i] == '\"')
	{
		if (!find_qoutes_supp(str, i, quotes))
			return (0);
	}
	return (1);
}
