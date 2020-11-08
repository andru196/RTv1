/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 21:09:05 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/08/25 20:38:09 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		s_precision(t_param *lst)
{
	if (lst->precision != -1)
		if ((int)ft_strlen(lst->str) > lst->precision)
			lst->str[lst->precision] = '\0';
}

int			p_precision(t_param *lst, t_list **ml)
{
	int		i;
	char	*hlp;
	char	*hlp2;

	i = ft_strlen(lst->str);
	if (lst->precision > i || (lst->width - 2 > i && lst->flag[4]))
	{
		i = lst->precision > (lst->width - 2 && lst->flag[4])
											? lst->precision : lst->width - 2;
		if (!(hlp = sm(ft_strnew(i - ft_strlen(lst->str)), ml, 0)))
			return (1);
		ft_memset(hlp, '0', i - ft_strlen(lst->str));
		hlp2 = sm(ft_strjoin(hlp, lst->str), ml, 0);
		del_lst(ml, 3, 0);
		lst->str = hlp2;
	}
	else if (!(long long)lst->param && !lst->precision)
		*lst->str = 0;
	return (0);
}

void		makestr_csp(t_param *lst, t_list **ml)
{
	char	*tmp;

	if (lst->type == 'c')
	{
		lst->str = sm((void *)ft_strnew(1), ml, 0);
		*(lst->str) = (char)lst->param;
	}
	else if (lst->type == 'p')
	{
		lst->str = sm(ft_itoa_base((long long)lst->param, 16), ml, 0);
		p_precision(lst, ml);
		tmp = sm((void *)ft_strjoin("0x", lst->str), ml, 0);
		del_win(ml, lst->str);
		lst->str = tmp;
	}
	else if (lst->type == 's')
	{
		if (lst->param)
			lst->str = sm(ft_strdup((char *)lst->param), ml, 0);
		else
			lst->str = sm(ft_strdup("(null)"), ml, 0);
		s_precision(lst);
	}
}
