/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 00:22:23 by andru             #+#    #+#             */
/*   Updated: 2020/12/14 20:56:19 by andru            ###   ########.fr       */
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

int scene_intersect(const t_figlst *lst, const t_coord orig, const t_coord dir, 
				t_coord *hit, t_coord *N, t_material *material, int flag)
{
	t_sphere	*sph;
	double		dist = 99999999999999999999999999999999999999999999999999999.;
	double		d;

	while (lst)
	{
		if (lst->kind == f_sphere)
		{
			sph = lst->figure;
			if (ray_intersect_spher(sph, orig, dir, &d) && d < dist)
			{
				dist = d;
				*hit = sum_coord(orig, mult_coord_sca(dir, d));
				*N = get_sphere_normal(sph->center, *hit);
				*material = lst->mater;
			}
		}
		else if (lst->kind == f_plane)
		{
			t_plane *pln = lst->figure;
			if (ray_intersect_plane(pln, orig, dir, &d) && d < dist) 
			{
				dist = d;
				*hit = sum_coord(orig, mult_coord_sca(dir, d));
				*N = get_plane_normal(pln->n, dir);
				*material = lst->mater;
			}
		}
		else if (lst->kind == f_cylinder)
		{
			double d;
			t_cylind *cyl = lst->figure;
			double m;
			if (ray_intersect_cylinder(cyl, orig, dir, &d, &m) && d < dist) 
			{
				dist = d;
				*hit = sum_coord(orig, mult_coord_sca(dir, d));
				*N = get_cylinder_normal(cyl->center, *hit, cyl->v, m);
				*material = lst->mater;
			}
		}
		else if (lst->kind == f_cone)
		{
			double d;
			t_cone *con = lst->figure;
			double m;
			if (ray_intersect_cone(con, orig, dir, &d, &m) && d < dist)
			{
				*hit = sum_coord(orig, mult_coord_sca(dir, d));
				*N = get_cone_normal(con->c, *hit, con->v, con->k, m);
				*material = lst->mater;
			}
		}
		lst = lst->next;
	}
	return dist < 1000 && dist >= 0.1;
}

t_coord cast_ray(const t_coord orig, const t_coord dir, const t_figlst *figlst, t_list *lights)
{
	t_figlst *rez;
	t_coord hit;
	t_coord N; 
	t_material material;

	if (!(scene_intersect(figlst, orig, dir, &hit, &N, &material, 1)))
			return init_coord(0, 0, 0);
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

void render(const t_figlst *figures, int *data, t_list *lights, t_coord orig)
{
	const int   fov = PI / 2.;
	size_t		j;

	j = 0;
	for (; j < HEIGHT; j++) 
	{
		for (size_t i = 0; i< WIDTH; i++)
		{
			float x =  (2*(i + 0.5)/(float)WIDTH  - 1)*tan(fov/2.)*WIDTH/(float)HEIGHT;
			float y = -(2*(j + 0.5)/(float)HEIGHT - 1)*tan(fov/2.);
			t_coord dir = normalize(init_coord(x, y, -1));
			t_coord c= cast_ray(orig, dir, figures, lights);			
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
}