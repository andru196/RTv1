/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 22:22:12 by andru             #+#    #+#             */
/*   Updated: 2020/12/14 21:26:10 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_figlst	*init_figure(t_figure fig)
{
	t_figlst	*rez;
	void		*content;

	if (!(rez = ft_memalloc(sizeof(t_figlst))))
		return (0);
	rez->kind = fig;
	return (rez);
}

t_coord init_coord(double x, double y, double z)
{
	t_coord p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}
