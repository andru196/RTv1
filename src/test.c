/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 00:22:23 by andru             #+#    #+#             */
/*   Updated: 2020/12/12 19:02:03 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** ??????I - N*2.f*(I*N)
*/
t_coord	reflect(t_coord I, t_coord N)
{
    return min_coord(I,
		mult_coord_sca(N,
			((
				ska_mult_coord(I, N)*
			2.f))));
}

double	sgn(double num)
{
	if (num > 0)
		return (1);
	if (num == 0)
		return (0);
	return (-1);
}

int scene_intersect(const t_figlst *lst, const t_coord orig, const t_coord dir, 
				t_coord *hit, t_coord *N, t_material *material, int flag)
{
	t_sphere	*sph;
	double		spheres_dist = 99999999999999999999999999999999999999999999999999999.;
	double		dist_i = spheres_dist;

	double checkerboard_dist = 99999999999999999999999999999999999999999999999999999.;
	while (lst)
	{
		if (lst->kind == f_sphere)
		{
			sph = lst->figure;
			if (ray_intersect_spher(sph, orig, dir, &dist_i) && dist_i < spheres_dist)
			{
				spheres_dist = dist_i;
				*hit = sum_coord(orig, mult_coord_sca(dir, dist_i));
				*N = normalize(min_coord(*hit, sph->center));
				*material = sph->mater;
			}
		}
		else if (lst->kind == f_plane)
		{
			double d;
			t_plane *pln = lst->figure;
			if (ray_intersect_plane(pln, orig, dir, &d)) 
			{
				if (d < checkerboard_dist)
					checkerboard_dist = d;
				if (checkerboard_dist < spheres_dist && d == checkerboard_dist)
				{
					*hit = sum_coord(orig, mult_coord_sca(dir, d));
					*N = (mult_coord_sca(pln->n, -sgn(ska_mult_coord(dir, pln->n))));
					*material = pln->mater;
				}
			}
		}
		else if (lst->kind == f_cylinder)
		{
			double d;
			t_cylind *pln = lst->figure;
			double m;
			if (ray_intersect_cylinder(pln, orig, dir, &d, &m)) 
			{
				if (d < checkerboard_dist)
					checkerboard_dist = d;
				if (checkerboard_dist < spheres_dist && d == checkerboard_dist)
				{
					*hit = sum_coord(orig, mult_coord_sca(dir, d));
					*N = normalize(min_coord(min_coord(*hit, pln->center), mult_coord_sca(pln->v, m)));
					*material = pln->mater;
				}
			}
		}
		else if (lst->kind == f_cone)
		{
			double d;
			t_cone *con = lst->figure;
			double m;
			if (ray_intersect_cone(con, orig, dir, &d, &m)) 
			{
				if (d < checkerboard_dist)
					checkerboard_dist = d;
				if (checkerboard_dist < spheres_dist && d == checkerboard_dist)
				{
					*hit = sum_coord(orig, mult_coord_sca(dir, d));
					*N = normalize(
						min_coord(min_coord(*hit, con->c), mult_coord_sca(con->v, m*(con->k * con->k  + 1)))
					);
					*material = con->mater;
				}
			}
		}
		lst = lst->next;
	}
	double rezzzz = spheres_dist > checkerboard_dist ? checkerboard_dist  : spheres_dist;

//	if (flag && checkerboard_dist != 99999999999999999999999999999999999999999999999999999.)
//		printf("%lf  %lf  %lf\n", rezzzz, spheres_dist, checkerboard_dist);

	return rezzzz < 1000 && rezzzz >= 0;
}

t_coord cast_ray(const t_coord orig, const t_coord dir, const t_figlst *figlst, t_list *lights)
{
	t_figlst *rez;
	t_coord hit;
	t_coord N; 
	t_material material;

	if (!(scene_intersect(figlst, orig, dir, &hit, &N, &material, 1)))
			return init_coord(0.2, 0.2, 0.2);
	double diffuse_light_intensity = 0, specular_light_intensity = 0;
	while (lights)
	{
		t_light light = *(t_light *)(lights->content);
        t_coord light_dir = normalize(min_coord(light.position, hit));

        t_coord shadow_orig;
		if (ska_mult_coord(light_dir, N) < 0)
			shadow_orig = min_coord(hit, mult_coord_sca(N, 1e-3));
		else
			shadow_orig = sum_coord(hit, mult_coord_sca(N, 1e-3)); // checking if the point lies in the shadow of the lights[i]
        t_coord shadow_pt, shadow_N;
        t_material tmpmaterial;

        if (scene_intersect(figlst, shadow_orig, light_dir, &shadow_pt, &shadow_N, &tmpmaterial, 0)
			&& norm(min_coord(shadow_pt, shadow_orig)) <
												norm(min_coord(light.position, hit)))
		{
			lights = lights->next;
			continue;
		}
		
		double num = ska_mult_coord(light_dir,N);
    	diffuse_light_intensity  += light.intensity * (0 > num ? 0 : num);
		num = ska_mult_coord(
			reflect(light_dir, N), dir);
		specular_light_intensity += powf(num > 0 ? num : 0, material.specular_exponent) * light.intensity;
		lights = lights->next;
	}
	return sum_coord(mult_coord_sca(mult_coord_sca(material.diffuse_color, diffuse_light_intensity > 1 ?
		1 : diffuse_light_intensity), material.albedo[0]), mult_coord_sca(mult_coord_sca(init_coord(1., 1., 1.),
			specular_light_intensity), material.albedo[1]));
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
			t_coord c= cast_ray(init_coord(0,0,0), dir, figures, lights);			
			{
				double max = c.x > c.y && c.x > c.z ? c.x
								: c.y > c.x && c.y > c.z ? c.y
								: c.z;
				if (max > 1)
					c = mult_coord_sca(c,(1./max));
			}
			
			*data++ = (((int)(c.x * 255)) << 16)
				| (((int)(c.y * 255)) << 8)
				| ((int)(c.z * 255));
		}
	}
	free(framebuffer);
}