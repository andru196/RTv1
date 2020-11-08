/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 17:38:12 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/06/30 17:38:14 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	g_edit(t_param *lst, t_list **ml)
{
	char *str;

	if (!ft_charinstr("gG", lst->type))
		return ;
	lst->precision = lst->precision == -1 ? 4 : lst->precision;
	pr_f(lst, ml);
	str = lst->str;
	while (*str != '.')
		str++;
	str += lst->precision;
	while (*str == '0')
	{
		if (*(str + 1) < '5' || *(str + 1) == '\0')
			lst->precision--;
		str--;
	}
	lst->type--;
}
