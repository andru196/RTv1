/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_multy_thread.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:42:30 by andru             #+#    #+#             */
/*   Updated: 2020/11/01 22:20:03 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

inline static t_compl	init_complex(double re, double im)
{
    t_compl	complex;
    
    complex.re = re;
    complex.im = im;
    return (complex);
}

void	stupid_fun(t_cont *cont, double r, double shift[2], int max_iteration)
{
	t_fract	fractal;
	int		width;
	int		height;

	width = cont->img->width;
	height = cont->img->height;
	fractal.min = init_complex((-2.0L + shift[0]) * r, (-2.0L + shift[1]) * r);
	fractal.max.re = (2.0L + shift[0]) * r;
	fractal.max.im = (fractal.min.im + (fractal.max.re - fractal.min.re)
		* height / width);
	fractal.factor = init_complex((fractal.max.re - fractal.min.re) /
		(width - 1), (fractal.max.im - fractal.min.im) / (height - 1));
	fractal.k = cont->k;
	fractal.iteration = 50 * fabs(log(r)) + max_iteration /
					(cont->current_set == julia_set ? 10 : 1);
	if (!cont->clcomponets.is_connected)
		cl_try_init_connect(&cont->clcomponets, "hello.cl", cont->current_set);
	if (cont->clcomponets.is_connected && cl_set_param(&cont->clcomponets,
		fractal, cont->img, cont->current_set == julia_set))
			cl_read_img(&cont->clcomponets, cont->img);
	else
		(cont->draw_fractal = stupid_fun_single_thread)(cont, r, shift, max_iteration);
}
