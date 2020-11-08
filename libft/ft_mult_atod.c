/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mult_atod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 16:00:12 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/06/24 16:01:14 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_mult_atod(char *arr, int n, char *rez, int count)
{
	int i;

	ft_bzero(rez, count + 1);
	i = count;
	while (i-- > 1)
	{
		rez[i] += arr[i] * n;
		while (rez[i] > 9)
		{
			rez[i] -= 10;
			rez[i - 1] += 1;
		}
	}
}
