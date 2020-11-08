/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 13:00:30 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/02/22 21:17:37 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char		*result;
	long int	copy_n;
	int			r;

	copy_n = n;
	r = n < 0 ? 2 : 1;
	while (n /= 10)
		r++;
	if (!(result = (char *)malloc(sizeof(char) * (r + 1))))
		return (NULL);
	if (copy_n < 0)
	{
		result[0] = '-';
		copy_n *= -1;
	}
	result[r] = '\0';
	result[0] = copy_n == 0 ? '0' : result[0];
	while (copy_n)
	{
		result[r - 1] = (copy_n % 10) + '0';
		--r;
		copy_n /= 10;
	}
	return (result);
}
