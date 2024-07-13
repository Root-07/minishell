/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:34:01 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/21 21:34:11 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nbr, int *len)
{
	int	i;

	i = 0;
	if (nbr == -2147483648)
		ft_putstr("-2147483648", len);
	else
	{
		if (nbr < 0)
		{
			ft_putchr('-', len);
			nbr *= -1;
		}
		if (nbr > 9)
		{
			ft_putnbr(nbr / 10, len);
			nbr %= 10;
		}
		ft_putchr(nbr + '0', len);
	}
}
