/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 14:49:28 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/01/19 13:20:43 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	result;
	int				count;

	result = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		result *= (-1);
	}
	count = 1;
	while (result / count >= 10)
		count *= 10;
	while (count > 0)
	{
		ft_putchar_fd('0' + result / count, fd);
		result %= count;
		count /= 10;
	}
}
