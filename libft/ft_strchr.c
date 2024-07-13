/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:21:17 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/16 20:08:56 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *str, int c)
{
	char	s;
	int		i;

	s = (char )c;
	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == s)
			return (&str[i]);
		i++;
	}
	if (!c)
		return ((char *)str);
	return (NULL);
}
