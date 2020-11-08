/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_single_thread.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 23:19:25 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/11/01 22:20:22 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline void	set_fractal(t_fract *f, double shift[2], t_img *img, double r)
{
	f->min.re = (-2.0L + shift[0]) * r;
	f->max.re = (2.0L + shift[0]) * r;
	f->min.im = (-2.0L + shift[1]) * r;
	f->max.im = (f->min.im + (f->max.re - f->min.re) * img->height / img->width);
	f->factor.re = (f->max.re - f->min.re) / (img->width - 1);
	f->factor.im = (f->max.im - f->min.im) / (img->height- 1);
}

void	*get_formula(t_set current_set)
{
	if (current_set == mandelbrot_set)
		return (mandelbrot_formula);
	if (current_set == burningship_set)
		return (ship_formula);
	else 
		return (julia_formula);
}

/*
** x_y_max[4]: x, y, max_x, max_y
*/
void	stupid_fun_single_thread(t_cont *cont, double r, double shift[2], int max_iteration)
{
	t_compl			c;
	t_fract			f;
	int				x_y_max[4];
	int				*data;
	void (*formula)	(int, int *, t_compl, t_compl);

	formula = get_formula(cont->current_set);
	x_y_max[2] = cont->img->width;
	x_y_max[3] = cont->img->height;
	set_fractal(&f, shift, cont->img, r);
	f.k = cont->k;
	max_iteration = 50 * fabs(log(r)) + max_iteration /
					(cont->current_set == julia_set ? 10 : 1);
	x_y_max[1] = -1;
	data = (int*)cont->img->data;
	while (++x_y_max[1] < x_y_max[2])
	{
		c.im = f.max.im - x_y_max[1] * f.factor.im;
		x_y_max[0] = -1;
		while (++x_y_max[0] < x_y_max[3])
		{
			c.re = f.min.re + x_y_max[0] * f.factor.re;
			formula(max_iteration, data++, c, f.k);
		}
	}
}
