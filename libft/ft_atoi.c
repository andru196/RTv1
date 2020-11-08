/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 12:53:21 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/01/19 13:22:25 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				minus;
	long long int	result;

	minus = 1;
	result = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		++str;
	if (*str == '-')
		minus = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		result = (*str - '0') + (10 * result);
		++str;
		if (result < 0)
			return (minus == -1 ? 0 : -1);
	}
	return (result * minus);
}
