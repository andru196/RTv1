/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 00:22:23 by andru             #+#    #+#             */
/*   Updated: 2020/11/13 22:04:01 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
t_coord    normalize(t_coord p)
{
	double w = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
	p.x /= w;
	p.y /= w;
	p.z /= w;
	return (p);
}

t_coord init_coord(double x, double y, double z)
{
	t_coord p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

int ray_intersect(const t_sphere *sph, const t_coord orig, const t_coord dir, double t0)
{
		t_coord L = min_coord(sph->center, orig);
		double tca = ska_mult_coord(L, dir);
		double d2 = ska_mult_coord(L, L) - tca * tca;
		if (d2 > sph->radius*sph->radius)
			return 0;
		double thc = sqrtf(sph->radius*sph->radius - d2);
		t0 = tca - thc;
		double t1 = tca + thc;
		if (t0 < 0)
			t0 = t1;
		if (t0 < 0)
			return 0;
		return 1;
}

t_coord cast_ray(const t_coord orig, const t_coord dir, const t_sphere *sphere)
{
	float sphere_dist = 99999999999999999999999999999999999999999999999999999.;
	if (!ray_intersect(sphere, orig, dir, sphere_dist)) {
		
		{
			t_coord def = {0.2, 0.7, 0.8};
			return def;
		}
	}
	t_coord def = {0.4, 0.4, 0.3};
	return def;
}

void render(const t_sphere *sphere, int *data) 
{
	const int   fov = PI / 2.;
	t_coord *framebuffer = malloc(WIDTH * HEIGHT * sizeof(t_clcomponents));
	size_t j;
	j = 0;
	for (; j < HEIGHT; j++) 
	{
		for (size_t i = 0; i< WIDTH; i++)
		{
			float x =  (2*(i + 0.5)/(float)WIDTH  - 1)*tan(fov/2.)*WIDTH/(float)HEIGHT;
			float y = -(2*(j + 0.5)/(float)HEIGHT - 1)*tan(fov/2.);
			t_coord dir = normalize(init_coord(x, y, -1));
			//framebuffer[i + j * WIDTH] 
			t_coord c= cast_ray(init_coord(0,0,0), dir, sphere);
			*data++ = (((int)(c.x * 255)) << 16)
				| (((int)(c.y * 255)) << 8)
				| ((int)(c.z * 255));
		}
	}
	free(framebuffer);
}