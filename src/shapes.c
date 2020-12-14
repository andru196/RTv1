/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 18:07:08 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/12/14 21:39:38 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int ray_intersect_cone(const  t_cone *con, const t_coord orig, const t_coord dir, double *t, double *m)
{
	t_coord x = min_coord(orig, con->c);	
	double a, b2, c, d4, s;
	s = ska_mult_coord(dir, con->v);

	a = ska_mult_coord(dir, dir) - (1 + con->k * con->k) * s * s;
	b2 = ska_mult_coord(dir, x) - (1 + con->k * con->k) * s * ska_mult_coord(x, con->v);
	c = ska_mult_coord(x, x) - ((1 + con->k * con->k)) * ska_mult_coord(x, con->v) * ska_mult_coord(x, con->v);
	d4 = b2 * b2 - a * c;

	*t = (-b2 + sqrt(d4)) / a;
	double t1 = (-b2 - sqrt(d4)) / a;
	if (*t < 0 && t1 < 0) return (0);
	*m = s * *t + ska_mult_coord(x, con->v);
	double m1 = s * t1 + ska_mult_coord(x, con->v);
	
	if ((t1 > 0 && t1 < *t && m1 >= 0 && m1 <= con->maxm)
		|| !(*m >= 0 && *m <= con->maxm))
	{
		*t = t1;
		*m = s * t1 + ska_mult_coord(x, con->v);
	}
	if ((*m >= 0 && *m <= con->maxm))
		return (1);
	else
		return 0;
}


int ray_intersect_cylinder(const t_cylind *cyl, const t_coord orig, const t_coord dir, double *t, double *m)
{
	double a,b,c, s, d4;

	s = ska_mult_coord(dir, cyl->v);
	t_coord x = min_coord(orig, cyl->center);
	
	a = ska_mult_coord(dir, dir) - s*s;
	if (a == 0)
		return (0);
	b = ska_mult_coord(dir, x) - s * ska_mult_coord(x, cyl->v);
	c = ska_mult_coord(x, x)
		- ska_mult_coord(x, cyl->v) * ska_mult_coord(x, cyl->v)
		- cyl->r * cyl->r;

	d4 = b*b - a*c;

	if (d4 < 0)
		return (0);	
	
	*t = (-b + sqrt(d4)) / a;
	double t1 = (-b - sqrt(d4)) / a;
	if (*t < 0 && t1 < 0) return (0);
	*m = s * *t + ska_mult_coord(x, cyl->v);
	double m1 = s * t1 + ska_mult_coord(x, cyl->v);
	
	if ((t1 > 0 && t1 < *t && m1 >= 0 && m1 <= cyl->maxm)
		|| !(*m >= 0 && *m <= cyl->maxm))
	{
		*t = t1;
		*m = s * t1 + ska_mult_coord(x, cyl->v);
	}
	if ((*m >= 0 && *m <= cyl->maxm))
		return (1);
	else
		return 0;
}

int ray_intersect_spher(const t_sphere *sph, const t_coord orig, const t_coord dir, double *t0)
{
		t_coord x = min_coord(orig, sph->center);
		double a = ska_mult_coord(dir, dir);
		double b = ska_mult_coord(dir, x);
		double c = ska_mult_coord(x, x) - sph->radius * sph->radius;

		double d = b*b - a*c;
		if (d < 0 || a == 0)
			return (0);
		*t0 = (-b + sqrt(d)) / a;
		double t = (-b - sqrt(d)) / a;
		if (t > 0 && t < *t0)
			*t0 = t;
		if (t < 0 && *t0 < 0)
			return (0);
		return 1;
}

int ray_intersect_plane(const t_plane *pln, const t_coord orig, const t_coord dir, double *t)
{
	t_coord x = min_coord(orig, pln->c);

	double s = ska_mult_coord(dir, pln->n);
	if (s == 0)
		return (0);
	*t = (-ska_mult_coord(x, pln->n))
		/ s;
	return (*t > 0);
}

