/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:54:40 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/06/26 23:32:00 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		flags_c(t_param *el, t_list **ml)
{
	char	*tmp;

	tmp = el->str;
	el->width = el->width ? el->width : 1;
	el->str = (char *)sm(malloc(sizeof(char) * el->width), ml, 0);
	if (el->flag[1])
	{
		el->str[0] = *tmp;
		ft_memset((void *)el->str + 1, ' ', el->width - 1);
	}
	else
	{
		el->str[el->width - 1] = *tmp;
		ft_memset((void *)el->str, el->flag[4] ? '0' : ' ', el->width - 1);
	}
	del_win(ml, (void *)tmp);
}

static void		flags(t_param *el, int w, int s, t_list **ml)
{
	char	*tmp;

	tmp = el->str;
	el->str = sm(ft_strnew(w), ml, 0);
	if (el->flag[1])
	{
		el->str = ft_strcpy(el->str, tmp);
		el->str = ft_memset((void *)el->str + s, ' ', w - s) - s;
	}
	else
	{
		el->str = ft_strcpy(el->str + (w - s), tmp) - w + s;
		el->str = ft_memset((void *)el->str, el->flag[4] &&
		!((!(ft_isdigit(el->str[w - 1])) && el->type == 'f') ||
								el->precision != -1) ? '0' : ' ', w - s);
	}
	del_win(ml, (void *)tmp);
}

static void		di_flags(t_param *el, int s, int w)
{
	if (el->flag[1])
	{
		if (el->flag[0] || el->flag[3])
			el->str = ft_memmove(el->str + (*(int *)el->param >= 0), el->str, s)
													- (*(int *)el->param >= 0);
		if (el->flag[0])
			el->str[0] = (*(int *)el->param >= 0) ? '+' : el->str[0];
		else if (el->flag[3])
			el->str[0] = (*(int *)el->param >= 0) ? ' ' : el->str[0];
	}
	else if (el->flag[4] && w > s)
	{
		el->str[0] = (*(int *)el->param >= 0) && el->flag[3] ? ' ' : el->str[0];
		el->str[0] = (*(int *)el->param >= 0) && el->flag[0] ? '+' : el->str[0];
		el->str[0] = (*(int *)el->param < 0) ? '-' : el->str[0];
		el->str[w - s] = (*(int *)el->param < 0) ? '0' : el->str[w - s];
	}
	else
	{
		if (el->flag[0] && *(int *)el->param >= 0)
			el->str[w - s - 1] = '+';
		else if (el->flag[3] && *(int *)el->param >= 0)
			el->str[w - s - 1] = ' ';
	}
}

static void		oxb_flags(t_param *el, int s, int w)
{
	if (el->flag[2] && (*(int *)el->param != 0 || el->type == 'o'))
	{
		if (el->flag[1])
		{
			el->str = ft_memmove(el->str + (el->type == 'o' ? 1 : 2),
									el->str, s) - (el->type == 'o' ? 1 : 2);
			if (el->type == 'o')
				el->str[0] = '0';
			else
			{
				el->str[0] = '0';
				el->str[1] = el->type;
			}
		}
		else if (el->flag[4])
		{
			if (el->type != 'o')
				el->str[1] = el->type;
		}
		else
		{
			el->str[w - s - 1] = (el->type == 'o' ? '0' : el->type);
			el->str[w - s - 2] = el->type == 'o' ? el->str[w - s - 2] : '0';
		}
	}
}

void			check_flags(t_param *el, t_list **ml)
{
	int		w;
	int		s;

	s = (int)ft_strlen(el->str);
	w = el->width >= s ? el->width : s;
	if (ft_charinstr("difFeEGg", el->type))
	{
		w = ((el->flag[0] || el->flag[3]) && (*(int *)el->param >= 0) && w <= s)
																	? w + 1 : w;
		flags(el, w, s, ml);
		di_flags(el, s, w);
	}
	else if (el->type == 'o' || el->type == 'x' || el->type == 'X')
	{
		if (el->flag[2] && el->type == 'o' && *(int *)el->param != 0)
			w = w <= s && *el->str != '0' ? w + 1 : w;
		else if (el->flag[2] && *(int *)el->param != 0)
			w = w <= s ? w + 2 : w;
		flags(el, w, s, ml);
		oxb_flags(el, s, w);
	}
	else if ((ft_charinstr("spub", el->type)))
		flags(el, w, s, ml);
	else
		flags_c(el, ml);
}
