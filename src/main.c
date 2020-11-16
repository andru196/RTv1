/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:58:11 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/11/16 22:09:26 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	((t_sphere*)rez[1]->figure)->center = init_coord(-8, 1, -15);
	((t_sphere*)rez[1]->figure)->radius = 2;
	t_material mat;
	mat.diffuse_color = init_coord(1, 1, 1);
	((t_sphere*)rez[1]->figure)->mater = mat;

	rez[1]->next = init_figure(f_sphere);
	rez[1] = rez[1]->next;
	((t_sphere*)rez[1]->figure)->center = init_coord(-10, 3, -13);
	((t_sphere*)rez[1]->figure)->radius = 4;
	mat.diffuse_color = init_coord(0.5, 1, 0);
	((t_sphere*)rez[1]->figure)->mater = red_rubber;

	rez[1]->next = init_figure(f_sphere);
	rez[1] = rez[1]->next;
	((t_sphere*)rez[1]->figure)->center = init_coord(0.5, 1, -5);
	((t_sphere*)rez[1]->figure)->radius = 1.5;
	mat.diffuse_color = init_coord(0.33, 0.33, 0.33);
	((t_sphere*)rez[1]->figure)->mater = ivory;

	rez[1]->next = init_figure(f_sphere);
	rez[1] = rez[1]->next;
	((t_sphere*)rez[1]->figure)->center = init_coord(0.5, 2, -5);
	((t_sphere*)rez[1]->figure)->radius = 1.5;
	mat.diffuse_color = init_coord(0.7, 0, 0.1);
	((t_sphere*)rez[1]->figure)->mater = red_rubber;

	rez[1]->next = init_figure(f_sphere);
	rez[1] = rez[1]->next;
	((t_sphere*)rez[1]->figure)->center = init_coord(0, 0, -25);
	((t_sphere*)rez[1]->figure)->radius = 1.5;
	mat.diffuse_color = init_coord(0, 0, 0.9);
	((t_sphere*)rez[1]->figure)->mater = ivory;
	return rez[0];
}

t_list	*get_lights()
{
	t_light light;
	t_list *rez;

	light.intensity = 0.5;
	light.position = init_coord(0, -1, -1);
	rez = ft_lstnew(&light, sizeof(t_light));

	light.intensity = 0.8;
	light.position = init_coord(10, -11, -11);
	rez->next = ft_lstnew(&light, sizeof(t_light));
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
