/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_converter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 17:43:41 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/10/21 01:17:56 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			convert_f(t_param *lst, va_list factor, t_list **ml)
{
	if (!(search_size(lst->size)))
	{
		lst->param = (double *)sm(malloc(sizeof(double)), ml, 0);
		*(double *)lst->param = (double)va_arg(factor, double);
	}
	else if (lst->size[3])
	{
		lst->param = (double *)sm(malloc(sizeof(double)), ml, 0);
		*(double *)lst->param = va_arg(factor, double);
	}
	else if (lst->size[4])
	{
		lst->param = (long double *)sm(malloc(sizeof(long double)), ml, 0);
		*(long double *)lst->param = (long double)va_arg(factor, long double);
	}
}

static void			convert_csp(t_param *lst, va_list factor)
{
	if (lst->type == 's')
		lst->param = va_arg(factor, char *);
	else if (lst->type == 'c' || lst->type == 'q')
		lst->param = (void *)(unsigned long)va_arg(factor, int);
	else if (lst->type == 'p')
		lst->param = va_arg(factor, void *);
}

static void			convert_uoxb(t_param *lst, va_list factor)
{
	if (!(search_size(lst->size)))
		*(UND *)lst->param = va_arg(factor, UND);
	else if (lst->size[0])
		*(UC *)lst->param = (UC)va_arg(factor, UND);
	else if (lst->size[2])
		*(ULL *)lst->param =
					(ULL)va_arg(factor, ULL);
	else if (lst->size[3])
		*(UL *)lst->param =
					(UL)va_arg(factor, UL);
	else if (lst->size[1])
		*(US *)lst->param =
					(US)va_arg(factor, UND);
}

static void			convert_di(t_param *lst, va_list factor)
{
	if (!(search_size(lst->size)))
		*(int *)lst->param = va_arg(factor, int);
	else if (lst->size[0])
		*(char *)lst->param = (char)va_arg(factor, int);
	else if (lst->size[2])
		*(long long int *)lst->param =
						(long long int)va_arg(factor, long long int);
	else if (lst->size[3])
		*(long int *)lst->param = (long int)va_arg(factor, long int);
	else if (lst->size[1])
		*(short *)lst->param = (short)va_arg(factor, int);
}

int					convert_param(t_param *lst, va_list factor, t_list **ml)
{
	while (lst)
	{
		if (ft_charinstr("di", lst->type))
		{
			lst->param = sm(malloc(sizeof(long long int)), ml, 0);
			convert_di(lst, factor);
		}
		else if (ft_charinstr("uoxXb", lst->type))
		{
			lst->param = (void *)sm(malloc(sizeof(ULL)), ml, 0);
			convert_uoxb(lst, factor);
		}
		else if (ft_charinstr("cspq", lst->type))
			convert_csp(lst, factor);
		else if (ft_charinstr(doubleS, lst->type))
			convert_f(lst, factor, ml);
		lst = lst->next;
	}
	return (0);
}
