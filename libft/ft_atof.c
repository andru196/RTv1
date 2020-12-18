/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 18:59:10 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/12/18 19:12:41 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *str)
{
	double	rez;
	double	pow;
	char	sign;

	while (ft_isspace(*str))
		str++;
	rez = 0;
	sign = *str == '-' ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while ((*str && ft_isdigit(*str)))
		rez = *str++ - '0' + rez * 10.;
	pow = 1;
	if (*str++ == '.')
		while (ft_isdigit(*str) && (pow /= 10))
			rez += (*str++ - '0') * pow;
	return (rez * (double)sign);
}
