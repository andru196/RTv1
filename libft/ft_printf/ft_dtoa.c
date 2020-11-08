/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:40:18 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/06/26 18:32:39 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_some(long double *n, char *str, int cheat_i, int cheat_j)
{
	char					arr[2000];
	char					rez[4000];
	char					pow[2000];
	unsigned long long int	*man;
	short					*par;

	man = (unsigned long long int *)n;
	ft_bzero(rez, 4000);
	ft_bzero(arr, 2000);
	par = ((short *)man) + 4;
	ft_utoa(*man, arr + 2000 - 21);
	ft_power_for_two(*par - 0x3fff - 63, pow);
	ft_mult(arr, pow, rez);
	while (rez[cheat_i] == 0 && cheat_i < 4000)
		cheat_i++;
	cheat_j = cheat_i;
	while (cheat_j < 4000)
		*str++ = rez[cheat_j++] + '0';
	*n = 0;
	return (4000 - cheat_i - 1);
}

static int		int_filler(long double *n, char *str)
{
	unsigned long long	int_n;
	int					i;
	int					rez;

	i = 1;
	if (*n - 1 <= 0xffffffffffffffff)
	{
		int_n = (unsigned long long)*n;
		if (!int_n)
			*str = '0';
		while (int_n /= 10)
			i++;
		rez = --i + 1;
		int_n = (unsigned long long)*n;
		*n = (*n - (long double)int_n) * 10;
		while (int_n)
		{
			str[i--] = (int)(int_n % 10) + '0';
			int_n /= 10;
		}
	}
	else
		rez = ft_some(n, str, 0, 0);
	return (rez);
}

static int		ft_check_num(long double *nbr, char **rez)
{
	unsigned short		*par;
	unsigned long long	*part1;

	par = ((unsigned short *)nbr) + 4;
	part1 = (unsigned long long *)nbr;
	if (*par == 0x8000 && *part1 == 0)
		*rez = ft_strdup("-0.0");
	else if (*par == 0x7fff && *part1 == 0xffffffffffffffff)
		*rez = ft_strdup("nan");
	else if (*par == 0x7fff)
		*rez = ft_strdup("inf");
	else if (*par == 0xffff)
		*rez = ft_strdup("-inf");
	else
		return (1);
	return (0);
}

char			*ft_dtoa(long double nbr)
{
	char		*rez;
	long double	n;
	int			i;

	n = nbr < 0 ? -nbr : nbr;
	if (ft_check_num(&nbr, &rez))
	{
		if (!(rez = ft_strnew(1000)))
			return (NULL);
		if (nbr < 0)
			*rez++ = '-';
		if ((i = int_filler(&n, rez)) < 1000)
			rez[i] = '.';
		while (++i < 1000)
		{
			rez[i] = (int)n + '0';
			n = (n - (long double)(rez[i] - '0')) * 10.0;
		}
		rez[i] = '\0';
	}
	return (rez - (nbr < 0 ? 1 : 0));
}
