/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_coord_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 01:09:19 by andru             #+#    #+#             */
/*   Updated: 2020/11/14 01:17:26 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_coord sum_coord(t_coord c1, t_coord c2)
{
	c1.x += c2.x;
	c1.y += c2.y;
	c1.z += c2.z;
	return (c1);
}

t_coord min_coord(t_coord c1, t_coord c2)
{
	c1.x -= c2.x;
	c1.y -= c2.y;
	c1.z -= c2.z;
	return (c1);
}

double ska_mult_coord(t_coord c1, t_coord c2)
{
	return (c1.x * c2.x + c1.y * c2.y + c1.z * c2.z);
}

t_coord	vect_mult_coord(t_coord c1, t_coord c2)
{
	t_coord rez;

	rez.x = c1.y * c2.z - c2.y * c1.z;
	rez.y = -(c1.x * c2.z - c1.z * c2.x);
	rez.z = c1.x * c2.y - c1.y * c2.x;
	return (rez);
}

t_coord	mult_coord_sca(t_coord c1, double n)
{
	c1.x *= n;
	c1.y *= n;
	c1.z *= n;
	return (c1);
}
