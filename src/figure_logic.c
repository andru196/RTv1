/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 22:22:12 by andru             #+#    #+#             */
/*   Updated: 2020/12/18 18:12:34 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		add_fig(t_figlst **frst, t_figlst *el)
{
	el->next = *frst;
	*frst = el;
}

t_figlst	*init_figure(t_figure fig)
{
	t_figlst	*rez;
	void		*content;

	if (!(rez = ft_memalloc(sizeof(t_figlst))))
		return (0);
	rez->mater.albedo[0] = 0.6;
	rez->mater.albedo[1] = 0.6;
	rez->mater.refractive_index = 0.9;
	rez->mater.specular_exponent = 13;
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
