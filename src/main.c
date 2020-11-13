/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:58:11 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/11/13 22:56:30 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_figlst		*test_list()
{
	t_figlst	*rez[2];
	double		radius = 2;

	rez[0] = init_figure(f_sphere);
	rez[1] = rez[0];
	((t_sphere*)rez[1]->figure)->center = init_coord(-8, 1, -15);
	((t_sphere*)rez[1]->figure)->radius = 2;
	((t_sphere*)rez[1]->figure)->color = init_coord(1, 1, 1);;
	rez[1]->next = init_figure(f_sphere);
	rez[1] = rez[1]->next;
	((t_sphere*)rez[1]->figure)->center = init_coord(-10, 3, -13);
	((t_sphere*)rez[1]->figure)->radius = 4;
	((t_sphere*)rez[1]->figure)->color = init_coord(0.5, 1, 0);
	rez[1]->next = init_figure(f_sphere);
	rez[1] = rez[1]->next;
	((t_sphere*)rez[1]->figure)->center = init_coord(0.5, 1, -5);
	((t_sphere*)rez[1]->figure)->radius = 1.5;
	((t_sphere*)rez[1]->figure)->color = init_coord(0.33, 0.33, 0.33);
	rez[1]->next = init_figure(f_sphere);
	rez[1] = rez[1]->next;
	((t_sphere*)rez[1]->figure)->center = init_coord(0.5, 2, -5);
	((t_sphere*)rez[1]->figure)->radius = 1.5;
	((t_sphere*)rez[1]->figure)->color = init_coord(0.7, 0, 0.1);
	return rez[0];
}

int		main(int argc, char **argv)
{
	t_cont	cont;
	t_img	*img;

	//if (argc != 2)
	//	return ft_printf("Usage: ./fractol [mandelbrot|ship|julia]\n") ? 1 : 1;
	ft_bzero(&cont, sizeof(t_cont));
	if (!(cont.mlx_ptr = mlx_init()) ||
		!(cont.mlx_win = mlx_new_window(cont.mlx_ptr, WIDTH, HEIGHT, argv[1])))
		ft_putendl("Start failed!");
	configure_events(&cont);
	img = new_image(cont.mlx_ptr, WIDTH, HEIGHT);
	t_figlst *l = test_list();
	render(l, img->data);
	cont.img = img;
	//set_default(&cont);
	mlx_put_image_to_window(cont.mlx_ptr, cont.mlx_win, img->img_ptr, 0, 0);
	mlx_loop(cont.mlx_ptr);
	return (0);
}
