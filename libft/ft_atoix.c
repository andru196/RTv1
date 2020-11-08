/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:33:08 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/11/04 16:05:45 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atoix(char *str)
{
	long long	rez;
	int			sign;
	int			method;

	while (ft_isspace(*str))
		str++;
	sign = *str == '-' ? -1 : 1;
	if (*str == '+' || *str == '-')
		str++;
	method = *str == '0' ? 8 : 10;
	method = method == 8 && ft_toupper(*(str + 1)) == 'X' ? 16 : method;
	while (*str == '0')
		str++;
	str = ft_toupper(*str) == 'X' ? str + 1 : str;
	rez = 0;
	while ((method == 10 && ft_isdigit(*str)) || (method == 8 && *str >= '0'
	&& *str <= '7') || (method == 16 && (ft_isdigit(*str) ||
	(ft_toupper(*str) >= 'A' && ft_toupper(*str) <= 'F'))))
	{
		rez *= method;
		rez += ft_isdigit(*str) ? *str - '0' : ft_toupper(*str) - 'A' + 10;
		str++;
	}
	return (rez * sign);
}
