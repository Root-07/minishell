/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:59:26 by rlabbiz           #+#    #+#             */
/*   Updated: 2023/06/21 21:34:08 by rlabbiz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_unsigned(unsigned int nbr, int *len)
{
	if (nbr > 9)
	{
		ft_putnbr(nbr / 10, len);
		nbr %= 10;
	}
	ft_putchr(nbr + '0', len);
}
