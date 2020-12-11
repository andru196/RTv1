/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:58:11 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/12/12 00:31:26 by andru            ###   ########.fr       */
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
	red_rubber.albedo[0] = 0.9;
	red_rubber.albedo[1] = 0.1;
	red_rubber.diffuse_color = init_coord(0.3, 0.1, 0.1);
	red_rubber.specular_exponent = 10;
	t_material	ivory;
	
	ivory.albedo[0] = 0.6;
	ivory.albedo[1] = 0.3;
	ivory.diffuse_color = init_coord(0.4, 0.4, 0.3);
	ivory.specular_exponent = 50;

	rez[0] = init_figure(f_sphere);
	rez[1] = rez[0];
	((t_sphere*)rez[1]->figure)->center = init_coord(8, 1, -15);
	((t_sphere*)rez[1]->figure)->radius = 2;
	t_material mat = ivory;
	mat.diffuse_color = init_coord(0.95, 0.95, 0.95);
	((t_sphere*)rez[1]->figure)->mater = mat;

	// rez[1]->next = init_figure(f_sphere);
	// rez[1] = rez[1]->next;
	// ((t_sphere*)rez[1]->figure)->center = init_coord(-10, 3, -13);
	// ((t_sphere*)rez[1]->figure)->radius = 4;
	// mat.diffuse_color = init_coord(0.5, 1, 0);
	// ((t_sphere*)rez[1]->figure)->mater = red_rubber;

	// rez[1]->next = init_figure(f_sphere);
	// rez[1] = rez[1]->next;
	// ((t_sphere*)rez[1]->figure)->center = init_coord(0.5, 1, -5);
	// ((t_sphere*)rez[1]->figure)->radius = 1.5;
	// mat.diffuse_color = init_coord(0.33, 0.33, 0.33);
	// ((t_sphere*)rez[1]->figure)->mater = ivory;

	// rez[1]->next = init_figure(f_sphere);
	// rez[1] = rez[1]->next;
	// ((t_sphere*)rez[1]->figure)->center = init_coord(-0.5, 0.3, -8);
	// ((t_sphere*)rez[1]->figure)->radius = 1.5;
	// mat.diffuse_color = init_coord(0.7, 0, 0.1);
	// ((t_sphere*)rez[1]->figure)->mater = red_rubber;

	// rez[1]->next = init_figure(f_sphere);
	// rez[1] = rez[1]->next;
	// ((t_sphere*)rez[1]->figure)->center = init_coord(0, 0, -25);
	// ((t_sphere*)rez[1]->figure)->radius = 1.5;
	// mat.diffuse_color = init_coord(0, 0, 0.9);
	// ((t_sphere*)rez[1]->figure)->mater = ivory;



	// t_material	plane_rubber;
	// plane_rubber.albedo[0] = 0.3;
	// plane_rubber.albedo[1] = 0.1;
	// plane_rubber.diffuse_color = init_coord(0.7, 0.1, 0.1);
	// plane_rubber.specular_exponent = 17;
	// rez[1]->next = init_figure(f_plane);
	// rez[1] = rez[1]->next;
	// ((t_plane*)rez[1]->figure)->n = init_coord(ZERO, ZERO, 1);
	// ((t_plane*)rez[1]->figure)->r = -30;
	// ((t_plane*)rez[1]->figure)->mater = plane_rubber;

	// t_material	plane;
	// plane.albedo[0] = 0.3;
	// plane.albedo[1] = 0.1;
	// plane.diffuse_color = init_coord(0.1, 0.1, 0.35);
	// plane.specular_exponent = 10;
	// rez[1]->next = init_figure(f_plane);
	// rez[1] = rez[1]->next;
	// ((t_plane*)rez[1]->figure)->n = init_coord(200, ZERO, ZERO);
	// ((t_plane*)rez[1]->figure)->r = 10000000;
	// ((t_plane*)rez[1]->figure)->mater = plane;

	rez[1]->next = init_figure(f_cylinder);
	rez[1] = rez[1]->next;
	((t_cylind*)rez[1]->figure)->v = normalize(init_coord(0, 1, 0.5));
	((t_cylind*)rez[1]->figure)->maxm = 2;
	((t_cylind*)rez[1]->figure)->center = init_coord(-1, 0,-5);
	((t_cylind*)rez[1]->figure)->r = 1;
	((t_cylind*)rez[1]->figure)->mater = red_rubber;
	return rez[0];
}

t_list	*get_lights()
{
	t_light light;
	t_list *rez;

	light.intensity = 0.9;
	light.position = init_coord(-9.3, 3.6, -2);
	rez = ft_lstnew(&light, sizeof(t_light));

	light.intensity = 0.9;
	light.position = init_coord(10, -11, 11);
	rez->next = ft_lstnew(&light, sizeof(t_light));
	
	light.intensity = 0.9;
	light.position = init_coord(-50.0, -0.0, -1);
	rez->next->next = ft_lstnew(&light, sizeof(t_light));
	return (rez);
}

int		main(int argc, char **argv)
{
	t_cont	cont;
	t_img	*img;

	//if (argc != 2)
	//	return ft_printf("Usage: ./trv1 <file>") ? 1 : 1;
	ft_bzero(&cont, sizeof(t_cont));
	if (!(cont.mlx_ptr = mlx_init()) ||
		!(cont.mlx_win = mlx_new_window(cont.mlx_ptr, WIDTH, HEIGHT, argv[1])))
		ft_putendl("Start failed!");
	configure_events(&cont);
	img = new_image(cont.mlx_ptr, WIDTH, HEIGHT);
	t_figlst *l = test_list();
	t_list *lights = get_lights();
	render(l, img->data, lights);
	cont.img = img;
	//set_default(&cont);
	mlx_put_image_to_window(cont.mlx_ptr, cont.mlx_win, img->img_ptr, 0, 0);
	mlx_loop(cont.mlx_ptr);
	return (0);
}
