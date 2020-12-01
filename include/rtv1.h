/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 22:21:32 by andru             #+#    #+#             */
/*   Updated: 2020/12/02 00:58:50 by andru            ###   ########.fr       */
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

typedef struct s_cont			t_cont;
typedef struct s_img			t_img;
typedef struct s_coordinate		t_coord;
typedef struct s_sphere			t_sphere;
typedef struct s_cone			t_cone;
typedef struct s_cylinder		t_cylind;
typedef struct s_plane			t_plane;
typedef unsigned char			byte;
typedef unsigned long long		t_llu;
typedef struct s_clcomponents	t_clcomponents;
typedef enum e_figure			t_figure;
typedef struct s_figlst			t_figlst;
typedef struct s_light			t_light;
typedef struct s_material		t_material;

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

enum					e_figure
{
	f_sphere = 1,
	f_plane = 2,
	f_cylinder,
	f_cone
};

struct 					s_figlst
{
	t_figure			kind;
	void				*figure;
	t_figlst			*next;
};


struct					s_cont
{
	void				*mlx_ptr;
	void				*mlx_win;
	int					mouse_click[2];
	int					is_move;
	t_img				*img;
	//t_clcomponents		clcomponets;
};

struct					s_coordinate
{
	double				x;
	double				y;
	double				z;
};

struct					s_material
{
	double				refractive_index;
    double				albedo[4];
    t_coord				diffuse_color;
    double				specular_exponent;
};

struct					s_plane
{
	t_coord				n;
	double				r;
	t_material			mater;
};

struct					s_sphere
{
	t_coord				center;
	t_material			mater;
	double				radius;
};

/*
** за центр принимаем центр "нижнего" основания
*/

struct					s_cylinder
{
	t_coord				center;
	unsigned			radius;
	unsigned			height;
};

struct					s_cone
{
	t_coord				center;
	unsigned			radius;
	unsigned			height;
};

struct					s_light
{
	t_coord				position;
    double				intensity;
};


t_img					*new_image(void *mlx_ptr, int width, int height);
void					configure_events(t_cont *c);
void					free_cont(t_cont *c);
void					stupid_fun(t_cont *img, double r, double shift[2],
																	int mi);
void					stupid_fun_single_thread(t_cont *cont, double r,
											double shift[2], int max_iteration);
t_coord					sum_coord(t_coord c1, t_coord c2);
t_coord					min_coord(t_coord c1, t_coord c2);
double 					ska_mult_coord(t_coord c1, t_coord c2);
t_coord					vect_mult_coord(t_coord c1, t_coord c2);
t_coord					mult_coord_sca(t_coord c1, double n);
void					render(const t_figlst *figures, int *data, t_list *lights);
t_coord					init_coord(double x, double y, double z);
t_figlst				*init_figure(t_figure fig);
double					norm(t_coord c);

#endif