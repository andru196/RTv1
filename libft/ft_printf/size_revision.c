/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_revision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:14:28 by ycorrupt          #+#    #+#             */
/*   Updated: 2020/10/21 01:17:56 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			ft_swap(short int *a, short int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void			size(short int s[5], char t)
{
	int i;

	if (ft_charinstr(INTS, t))
	{
		i = 4;
		s[i] = 0;
		ft_swap(&s[2], &s[3]);
		while (--i >= 0)
			if (s[i] == 1)
				ft_bzero((void *)s, i * 2);
		ft_swap(&s[2], &s[3]);
	}
	else if (ft_charinstr(doubleS, t))
	{
		if (s[4])
			ft_bzero((void *)s, 8);
		else if (s[3])
			ft_bzero((void *)s, 6);
		else
			ft_bzero((void *)s, 10);
	}
	else
		ft_bzero((void *)s, 10);
}

t_param				*size_revision(t_param *params)
{
	t_param	*el;

	el = params;
	while (el)
	{
		size(el->size, el->type);
		el = el->next;
	}
	return (params);
}
