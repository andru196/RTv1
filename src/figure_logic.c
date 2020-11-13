/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 22:22:12 by andru             #+#    #+#             */
/*   Updated: 2020/11/13 22:36:30 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_figlst	*init_figure(t_figure fig)
{
	t_figlst	*rez;
	void		*content;

	if (!(rez = malloc(sizeof(t_figlst))))
		return (0);
	rez->kind = fig;
	if (fig == f_cone)
		content = ft_memalloc(sizeof(t_cone));
	else if (fig == f_sphere)
		content = ft_memalloc(sizeof(t_sphere));
	else if (fig == f_plane)
		content = ft_memalloc(sizeof(t_plane));
	else
		content = ft_memalloc(sizeof(t_cylind));
	if (content == NULL)
	{
		free(rez);
		return (0);
	}
	rez->figure = content;
	rez->next = 0;
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
