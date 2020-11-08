/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 18:38:24 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/06/28 18:38:33 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	make_end(char *str, int ord, char type, long double nbr)
{
	int		i;
	char	rez[6];

	if (nbr != 0.0L)
	{
		i = 0;
		rez[i++] = type;
		ord = ord - (ord > 0);
		rez[i++] = ord < 0 ? '-' : '+';
		ord = ord < 0 ? -ord : ord;
		if (ord > 100)
		{
			rez[i++] = ord / 100 + '0';
			ord %= 100;
		}
		rez[i++] = ord / 10 + '0';
		rez[i++] = ord % 10 + '0';
		rez[i] = '\0';
		ft_strcat(str, rez);
	}
	else
	{
		ft_memset(str, 0, ft_strlen(str));
		ft_strcat(str, type == 'e' ? "0.0e+00" : "0.0E+00");
	}
}

int			makestr_e(t_param *lst, t_list **ml)
{
	int		ord;
	char	*str1;
	char	*str2;

	ord = 0;
	str1 = lst->str;
	if (!(str2 = sm(ft_strnew(ft_strlen(lst->str) + 6), ml, 0)))
		return (1);
	if (*lst->str == '-' && str1++)
		*str2++ = '-';
	while (*str1++ != '.')
		ord++;
	ord = *(str1 - ord - 1) == '0' ? -1 : ord;
	if (ord == -1)
		while (*str1 == '0' && ord--)
			str1++;
	*str2 = *(str1 - (ord > 0 ? ord + 1 : 0));
	*(str2 + 1) = '.';
	ft_memcpy(str2 + 2, str1 - (ord > 0 ? ord : -1),
			(ord > 0 ? ord - 1 : ft_strlen(str1)));
	ft_strcat(str2, ord > 0 ? str1 : "");
	make_end(str2, ord, lst->type, *(long double *)lst->param);
	del_win(ml, lst->str);
	return (0 * (int)(lst->str = str2 - (*(long double *)lst->param < 0.0L ||
(*((US *)lst->param + 4) == 0x8000 && *(long double *)lst->param == 0.0L))));
}
