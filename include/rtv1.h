/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:06:37 by ycorrupt          #+#    #+#             */
/*   Updated: 2020/11/08 17:25:42 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# define WIDTH 1024
# define HEIGHT 1024
# define PI 3.141592653589793238462643383279502884197169399375105820974944592
# define DELTA 1.5L
# define DELTA_MAXITER 100

typedef struct s_cont		t_cont;
typedef struct s_img		t_img;
typedef unsigned char		byte;
typedef unsigned long long	t_llu;

# include "cl_module.h"


struct					s_img
{
	void				*img_ptr;
	int 				bits_per_pixel;
	int 				size_line;
	int 				endian;
	byte				*data;
	int					width;
	int					height;
};

struct					s_cont
{
	void				*mlx_ptr;
	void				*mlx_win;
	int					mouse_click[2];
	int					is_move;
	t_img				*img;
	t_clcomponents		clcomponets;
};

t_img					*new_image(void *mlx_ptr, int width, int height);
void					configure_events(t_cont *c);
void					free_cont(t_cont *c);
void					stupid_fun(t_cont *img, double r, double shift[2],
																	int mi);
void					stupid_fun_single_thread(t_cont *cont, double r,
											double shift[2], int max_iteration);

#endif