/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:47:10 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/21 21:33:59 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex_(unsigned long long nbr, int *len)
{
	unsigned long long	i;
	char				*base;

	i = 16;
	base = "0123456789abcdef";
	if (nbr < 16)
	{
		ft_putchr(base[nbr], len);
	}
	else
	{
		ft_puthex_(nbr / i, len);
		ft_puthex_(nbr % i, len);
	}
}

void	ft_putadd(void *add, int *len)
{
	ft_putstr("0x", len);
	ft_puthex_((unsigned long long)add, len);
}
