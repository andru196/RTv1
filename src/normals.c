/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 20:37:32 by andru             #+#    #+#             */
/*   Updated: 2020/12/14 20:56:32 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static inline double	sgn(double num)
{
	if (num > 0)
		return (1);
	if (num == .0)
		return (0);
	return (-1);
}


inline t_coord get_plane_normal(t_coord n, t_coord dir)
{
	return (normalize(
				mult_coord_sca(n,
					-sgn(ska_mult_coord(dir, n)))));
}

inline t_coord get_sphere_normal(t_coord center, t_coord hit)
{
	return (normalize(min_coord(hit, center)));
}

inline t_coord get_cylinder_normal(t_coord center, t_coord hit, t_coord normal,
																	double m)
{
	return (normalize(min_coord(min_coord(hit, center),
												mult_coord_sca(normal, m))));
}

inline t_coord get_cone_normal(t_coord center, t_coord hit, t_coord normal,
															double k, double m)
{
	return normalize(min_coord(min_coord(hit, center),
									mult_coord_sca(normal, m * (k * k  + 1))));
}