/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:52:56 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/21 21:33:54 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_check(va_list ap, int c, int *len)
{
	if (c == '%')
		ft_putchr('%', len);
	else if (c == 'c')
		ft_putchr(va_arg(ap, int), len);
	else if (c == 's')
		ft_putstr(va_arg(ap, char *), len);
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(ap, int), len);
	else if (c == 'u')
		ft_putnbr_unsigned(va_arg(ap, unsigned int), len);
	else if (c == 'x' || c == 'X')
		ft_puthex(va_arg(ap, unsigned int), c, len);
	else if (c == 'p')
		ft_putadd(va_arg(ap, void *), len);
}

int	ft_printf(const char *content, ...)
{
	va_list	ap;
	int		i;
	int		len;

	va_start(ap, content);
	len = 0;
	i = 0;
	while (content[i] != '\0')
	{
		if (content[i] == '%')
		{
			i++;
			ft_check(ap, content[i], &len);
		}
		else
		{
			ft_putchr(content[i], &len);
		}
		i++;
	}
	return (len);
}
