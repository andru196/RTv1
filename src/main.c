/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:58:11 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/12/18 14:17:01 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//http://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
#include "rtv1.h"

#define ZERO 0.0000000000000000000000000000000000000000000000000000000000000001

static t_figlst		*test_list()
{
	t_figlst	*rez[2];
	double		radius = 2;

	t_material	red_rubber;
	t_material	ivory;
	{
		red_rubber.albedo[0] = 0.9;
		red_rubber.albedo[1] = 0.1;
		red_rubber.diffuse_color = init_coord(0.3, 0.1, 0.1);
		red_rubber.specular_exponent = 10;
		
		ivory.albedo[0] = 0.6;
		ivory.albedo[1] = 0.3;
		ivory.diffuse_color = init_coord(0.4, 0.4, 0.3);
		ivory.specular_exponent = 50;
	}
	
	rez[0] = init_figure(f_sphere);
	rez[1] = rez[0];
	(rez[1]->figure.sphere).center = init_coord(8, 1, -15);
	(rez[1]->figure.sphere).radius = 2;
	t_material mat = ivory;
	mat.diffuse_color = init_coord(0.95, 0.95, 0.95);
	(rez[1])->mater = mat;

	rez[1]->next = init_figure(f_sphere);
	rez[1] = rez[1]->next;
	(rez[1]->figure.sphere).center = init_coord(-10, -3, -13);
	(rez[1]->figure.sphere).radius = 4;
	mat.diffuse_color = init_coord(0.5, 1, 0);
	(rez[1])->mater = red_rubber;

	rez[1]->next = init_figure(f_sphere);
	rez[1] = rez[1]->next;
	(rez[1]->figure.sphere).center = init_coord(0.5, -4, -5);
	(rez[1]->figure.sphere).radius = 1.5;
	mat.diffuse_color = init_coord(0.33, 0.33, 0.33);
	(rez[1])->mater = ivory;

	rez[1]->next = init_figure(f_sphere);
	rez[1] = rez[1]->next;
	(rez[1]->figure.sphere).center = init_coord(-0.5, -3, -8);
	(rez[1]->figure.sphere).radius = 1.5;
	mat.diffuse_color = init_coord(0.7, 0, 0.1);
	(rez[1])->mater = red_rubber;

	rez[1]->next = init_figure(f_sphere);
	rez[1] = rez[1]->next;
	(rez[1]->figure.sphere).center = init_coord(0, 0, -25);
	(rez[1]->figure.sphere).radius = 1.5;
	mat.diffuse_color = init_coord(0, 0, 0.9);
	(rez[1])->mater = ivory;



	t_material	plane_rubber;
	plane_rubber.albedo[0] = 0.3;
	plane_rubber.albedo[1] = 0.1;
	plane_rubber.specular_exponent = 4;
	plane_rubber.diffuse_color = init_coord(0.1, 0.1, 0.6);

	rez[1]->next = init_figure(f_plane);
	rez[1] = rez[1]->next;
	(rez[1]->figure.plane).n = normalize(init_coord(ZERO, 0.5, 1));
	(rez[1]->figure.plane).c = init_coord(0, 0, -17);
	(rez[1])->mater = plane_rubber;

	t_material	plane;
	plane.albedo[0] = 0.7;
	plane.albedo[1] = 0.6;
	plane.diffuse_color = init_coord(0.1, 0.5, 0.35);
	plane.specular_exponent = 14;
	
	rez[1]->next = init_figure(f_plane);
	rez[1] = rez[1]->next;
	(rez[1]->figure.plane).n = init_coord(10, ZERO, ZERO);
	(rez[1]->figure.plane).c = init_coord(5, 1, 1);
	(rez[1])->mater = plane;

	rez[1]->next = init_figure(f_cylinder);
	rez[1] = rez[1]->next;
	(rez[1]->figure.cylinder).v = normalize(init_coord(0, -.6, 1));
	(rez[1]->figure.cylinder).maxm = 2;
	(rez[1]->figure.cylinder).center = init_coord(-1, 0,-5);
	(rez[1]->figure.cylinder).r = 1;
	(rez[1])->mater = red_rubber;

	rez[1]->next = init_figure(f_cone);
	rez[1] = rez[1]->next;
	(rez[1]->figure.cone).v = normalize(init_coord(0, 1, 0.5));
	(rez[1]->figure.cone).maxm = 2;
	(rez[1]->figure.cone).minm = 0;
	(rez[1]->figure.cone).c = init_coord(1, 0,-5);
	(rez[1]->figure.cone).k = 0.3;
	(rez[1])->mater = ivory;
	return rez[0];
}

t_list	*get_lights()
{
	t_light light;
	t_list *rez;

	light.intensity = 0.9;
	light.position = init_coord(-9.3, 3.6, -2);
	rez = ft_lstnew(&light, sizeof(t_light));

	light.intensity = 0.6;
	light.position = init_coord(10, 0, -11);
	rez->next = ft_lstnew(&light, sizeof(t_light));
	
	light.intensity = 0.3;
	light.position = init_coord(0, 0, 0);
	rez->next->next = ft_lstnew(&light, sizeof(t_light));

	light.intensity = 0.9;
	light.position = init_coord(-50.0, -0.0, -1);
	rez->next->next->next = ft_lstnew(&light, sizeof(t_light));
	return (rez);
}

int		main(int argc, char **argv)
{
	t_cont	cont;
	t_img	*img;

	//if (argc != 2)
	//	return ft_printf("Usage: ./rtv1 <file>") ? 1 : 1;
	ft_bzero(&cont, sizeof(t_cont));
	if (!(cont.mlx_ptr = mlx_init()) ||
		!(cont.mlx_win = mlx_new_window(cont.mlx_ptr, WIDTH, HEIGHT, "rtv1")))
		ft_putendl("Start failed!");
	configure_events(&cont);
	img = new_image(cont.mlx_ptr, WIDTH, HEIGHT);
	read_scene(&cont, argv[1]);
	render(cont.figures, (int *)img->data, cont.lights, init_coord(0, 0, 0));
	cont.img = img;
	//set_default(&cont);
	mlx_put_image_to_window(cont.mlx_ptr, cont.mlx_win, img->img_ptr, 0, 0);
	mlx_loop(cont.mlx_ptr);
	return (0);
}
