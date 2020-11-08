/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 19:52:21 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/01/19 13:15:25 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int	result;
	int				count;

	result = n;
	if (n < 0)
	{
		ft_putchar('-');
		result *= (-1);
	}
	count = 1;
	while (result / count >= 10)
		count *= 10;
	while (count > 0)
	{
		ft_putchar('0' + result / count);
		result %= count;
		count /= 10;
	}
}
