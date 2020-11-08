/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dioux.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 14:47:34 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/06/27 00:10:15 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			makestr_di(t_param *lst, t_list **ml)
{
	int res;

	res = 0;
	if (lst->size[0])
		lst->str = sm(ft_itoa_base((char)*(LL *)(lst->param), 10), ml, 0);
	else if (lst->size[1])
		lst->str = sm(ft_itoa_base((short)*(LL *)(lst->param), 10), ml, 0);
	else if (lst->size[3])
		lst->str = sm(ft_itoa_base((long)*(LL *)(lst->param), 10), ml, 0);
	else if (lst->size[2])
		lst->str = sm(ft_itoa_base(*(LL *)(lst->param), 10), ml, 0);
	else
		lst->str = sm(ft_itoa_base((int)*(LL *)(lst->param), 10), ml, 0);
	return (res);
}

static int	type_selector(char type, int *rez)
{
	*rez = 0;
	if (type == 'x' || type == 'X')
		*rez = 16;
	else if (type == 'b')
		*rez = 2;
	else if (type == 'o')
		*rez = 8;
	return (0);
}

int			makestr_oux(t_param *l, t_list **ml)
{
	int		i;
	int		s;
	int		res;

	res = type_selector(l->type, &s);
	if (l->size[0])
		l->str = sm(ft_itoa_base((UC) * (LL *)(l->param), s), ml, 0);
	else if (l->size[1])
		l->str = sm(ft_itoa_base((US) * (LL *)(l->param), s), ml, 0);
	else if (l->size[3])
		l->str = sm(ft_itoa_base((UL) * (LL *)(l->param), s), ml, 0);
	else if (l->size[2])
		l->str = sm(ft_itoa_base(*(ULL *)(l->param), s), ml, 0);
	else
		l->str = sm(ft_itoa_base((UND) * (LL *)(l->param), s), ml, 0);
	i = -1;
	if (l->type == 'X')
		while ((l->str)[++i])
			(l->str)[i] = ft_toupper((l->str)[i]);
	return (res);
}

int			precision_dioux(t_param *lst, t_list **ml)
{
	int		i;
	char	*hlp;
	char	*hlp2;

	i = ft_strlen(lst->str);
	if (lst->precision > i)
	{
		lst->precision += (*(int *)lst->param < 0) ? 1 : 0;
		hlp = (char *)sm(malloc(lst->precision - i + 1), ml, 0);
		ft_memset(hlp, '0', lst->precision - i);
		hlp[0] = (*(int *)lst->param < 0) ? '-' : hlp[0];
		lst->str[0] = (*(int *)lst->param < 0) ? '0' : lst->str[0];
		hlp[lst->precision - i] = '\0';
		hlp2 = (char *)sm(ft_strjoin(hlp, lst->str), ml, 0);
		del_lst(ml, 3, 0);
		lst->str = hlp2;
	}
	else if (lst->precision == 0 && *lst->str == '0' &&
									!(lst->flag[2] && lst->type == 'o'))
		*lst->str = 0;
	return (0);
}
