/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 00:22:23 by andru             #+#    #+#             */
/*   Updated: 2020/11/14 01:42:32 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
t_coord    normalize(t_coord p)
{
	double w = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
	if (w != 0)
	{
		p.x /= w;
		p.y /= w;
		p.z /= w;
	}
	return (p);
}


int ray_intersect(t_sphere *sph, const t_coord orig, const t_coord dir, double *t0)
{
		t_coord L = min_coord(sph->center, orig);
		double tca = ska_mult_coord(L, dir);
		double d2 = ska_mult_coord(L, L) - tca * tca;
		if (d2 > sph->radius*sph->radius)
			return 0;
		double thc = sqrtf(sph->radius*sph->radius - d2);
		*t0 = tca - thc;
		double t1 = tca + thc;
		if (*t0 < 0)
			*t0 = t1;
		if (*t0 < 0)
			return 0;		
		return 1;
}

int scene_intersect (t_figlst *lst, const t_coord orig, const t_coord dir, t_coord *hit, t_coord *N, t_material *material)
{
	t_sphere	*sph;
	double		spheres_dist = 99999999999999999999999999999999999999999999999999999.;
	double		dist_i = spheres_dist;

	while (lst)
	{
		sph = lst->figure;
		if (ray_intersect(sph, orig, dir, &dist_i) && dist_i < spheres_dist)
		{
			spheres_dist = dist_i;
            *hit = sum_coord(orig, mult_coord_sca(dir, dist_i));
            *N = normalize(min_coord(*hit, sph->center));
            *material = sph->mater;
		}
		lst = lst->next;
	}
	return spheres_dist < 1000;
}

t_coord cast_ray(const t_coord orig, const t_coord dir, const t_figlst *figlst, t_list *lights)
{
	t_figlst *rez;
	t_coord hit;
	t_coord N; 
	t_material material;

	if (!(scene_intersect(figlst, orig, dir, &hit, &N, &material)))
			return init_coord(0.2, 0.2, 0.2);
	double diffuse_light_intensity = 0;
	while (lights)
	{
		t_light light = *(t_light *)(lights->content);
        t_coord light_dir = normalize(min_coord(light.position, hit));
		double num = ska_mult_coord(light_dir,N);
    	diffuse_light_intensity  += light.intensity * (0 > num ? 0 : num);
		lights = lights->next;
	}
	return mult_coord_sca(material.diffuse_color, diffuse_light_intensity > 1 ?
		1 : diffuse_light_intensity);
}

void render(const t_figlst *figures, int *data, t_list *lights) 
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
			t_coord c= cast_ray(init_coord(0,0,0), dir, figures, lights);
			*data++ = (((int)(c.x * 255)) << 16)
				| (((int)(c.y * 255)) << 8)
				| ((int)(c.z * 255));
		}
	}
	free(framebuffer);
}