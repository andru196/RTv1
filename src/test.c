/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 00:22:23 by andru             #+#    #+#             */
/*   Updated: 2020/12/02 01:52:12 by andru            ###   ########.fr       */
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

t_coord	reflect(t_coord I, t_coord N)
{//////////////////////////////////////////////??????I - N*2.f*(I*N)
    return min_coord(I,
		mult_coord_sca(N,
			((
				ska_mult_coord(I, N)*
			2.f))));
}


int ray_intersect_spher(t_sphere *sph, const t_coord orig, const t_coord dir, double *t0)
{
		t_coord L = min_coord(sph->center, orig); //Обозначим s = C – A
		double tca = ska_mult_coord(L, dir); // sd
		double d2 = ska_mult_coord(L, L) - tca * tca; //s^2 - (sd)^2 где (d,s) — скалярное произведение векторов d и s
		if (d2 > sph->radius*sph->radius)
			return 0;
		double thc = sqrtf(sph->radius*sph->radius - d2); //r^2 - s^2 + (d,s)^2
		*t0 = tca - thc; //(d,s) - r^2 + s^2 + (d,s)^2
		double t1 = tca + thc; //s^2 + r^2 - s^2 - (d,s)^2
		if (*t0 < 0)
			*t0 = t1;
		if (*t0 < 0)
			return 0;		
		return 1;
}

int ray_intersect_plane(t_plane *pln, const t_coord orig, const t_coord dir, double *t)
{
		static double r = -1.0987654;
		static double rez = -1.0987654;
	
		if (ska_mult_coord(dir, pln->n) == .0)
			return (0);
		if (pln->r != r)
		{
			r = pln->r;
			rez = pln->r / sqrt(pln->n.x * pln->n.x + pln->n.y * pln->n.y + pln->n.z * pln->n.z);
		}
		*t = (rez - ska_mult_coord(dir, pln->n)) / ska_mult_coord(dir, pln->n);
		return *t > 0;
}

double	sgn(double num)
{
	if (num > 0)
		return (1);
	if (num == 0)
		return (0);
	return (-1);
}

int scene_intersect(t_figlst *lst, const t_coord orig, const t_coord dir, t_coord *hit, t_coord *N, t_material *material)
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
				if (checkerboard_dist < spheres_dist)
				{
					*hit = sum_coord(orig, mult_coord_sca(dir, d));
					*N = normalize(mult_coord_sca(pln->n, -sgn(ska_mult_coord(dir, pln->n))));
					*material = pln->mater;
				}
			}
		}
		lst = lst->next;
	}

	if (fabs(dir.y) > 1e-3 && 0) 
	{
        double d = -(orig.y + 4) / dir.y; // the checkerboard plane has equation y = -4
        t_coord pt = sum_coord(orig, mult_coord_sca(dir, d));
        if (d>0 && fabs(pt.x)<10 && pt.z<-10 && pt.z>-30 && d<spheres_dist) 
		{
            checkerboard_dist = d;
            *hit = pt;
            *N = init_coord(0,1,0);
            material->diffuse_color = ((int)(.5*hit->x+1000) + (int)(.5*hit->z)) & 1 
			? init_coord(1,1,1) : init_coord(1, .7, .3);
            material->diffuse_color = mult_coord_sca(material->diffuse_color, .3);
			material->albedo[0] = 0.9;
			material->albedo[1] = 0.1;
			material->specular_exponent = 10;
        }
    }
	return spheres_dist < 1000 || checkerboard_dist < 1000;
}

t_coord cast_ray(const t_coord orig, const t_coord dir, const t_figlst *figlst, t_list *lights)
{
	t_figlst *rez;
	t_coord hit;
	t_coord N; 
	t_material material;

	if (!(scene_intersect(figlst, orig, dir, &hit, &N, &material)))
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

        if (scene_intersect(figlst, shadow_orig, light_dir, &shadow_pt, &shadow_N, &tmpmaterial)
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