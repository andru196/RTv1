/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 22:21:32 by andru             #+#    #+#             */
/*   Updated: 2020/12/18 14:46:03 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>

typedef struct s_cont			t_cont;
typedef struct s_img			t_img;
typedef struct s_coordinate		t_coord;
typedef struct s_sphere			t_sphere;
typedef struct s_cone			t_cone;
typedef struct s_cylinder		t_cylind;
typedef struct s_plane			t_plane;
typedef unsigned char			byte;
typedef unsigned long long		t_llu;
typedef enum e_figure			t_figure;
typedef struct s_figlst			t_figlst;
typedef struct s_light			t_light;
typedef struct s_material		t_material;
typedef struct s_press			t_press;
typedef union u_gen_fig			t_gen_fig;

# define WIDTH 1024
# define HEIGHT 1024
# define PI 3.141592653589793238462643383279502884197169399375105820974944592
# define LIGHT_NAME "light"

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

# define FIG_NUMS 4
# define FIGURES_NAMES {"cylinder", "sphere", "plane", "cone", NULL}
# define FIGURES_TYPES {f_cylinder, f_sphere, f_plane, f_cone}

struct 					s_press
{
	char				shift;
	char				ctrl;
	char				alt;
	char				tab;
};

struct					s_cont
{
	void				*mlx_ptr;
	void				*mlx_win;
	int					is_move;
	t_img				*img;
	t_figlst			*figures;
	t_list				*lights;
	t_press				pressed_keys;
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
    double				albedo[2];
    t_coord				diffuse_color;
    double				specular_exponent;
};

struct					s_plane
{
	t_coord				c;
	t_coord				n;
};

struct					s_sphere
{
	t_coord				center;
	double				radius;
};

/*
** за центр принимаем центр "нижнего" основания
*/

struct					s_cylinder
{
	t_coord				center;
	t_coord				v;
	double				r;
	double				maxm;
};

/*
** C is the vertex of the cone
** V is the axis vector
** k is the tangent of half angle of the cone
** minm, maxm define cap points
*/
struct					s_cone
{
	t_coord				c;
	t_coord				v;
	double				k;
	double				minm;
	double				maxm;
};

union 					u_gen_fig
{
	t_cone				cone;
	t_sphere			sphere;
	t_plane				plane;
	t_cylind			cylinder;
};


struct 					s_figlst
{
	t_figure			kind;
	t_gen_fig			figure;
	t_material			mater;
	t_figlst			*next;
};

struct					s_light
{
	t_coord				position;
    double				intensity;
};

void					print_errno(int errnom, t_cont *c);
void					print_error(char *error, t_cont *c);
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
void					render(const t_figlst *figures, int *data, t_list *lights, t_coord orig);
t_coord					init_coord(double x, double y, double z);
t_figlst				*init_figure(t_figure fig);
void					add_fig(t_figlst **frst, t_figlst *el);
double					norm(t_coord c);
double					len_vect(t_coord c1, t_coord c2);
t_coord					normalize(t_coord p);
int						ray_intersect_plane(const t_plane *pln, const t_coord orig, const t_coord dir, double *t);
int						ray_intersect_spher(const t_sphere *sph, const t_coord orig, const t_coord dir, double *t0);
int						ray_intersect_cylinder(const t_cylind *cyl, const t_coord orig, const t_coord dir, double *t, double *m);
int						ray_intersect_cone(const t_cone *con, const t_coord orig, const t_coord dir, double *t0, double *m);
int						key_release(int keycode, void *param);
t_coord					get_sphere_normal(t_coord center, t_coord hit);
t_coord					get_plane_normal(t_coord n, t_coord dir);
t_coord 				get_cylinder_normal(t_coord center, t_coord hit,
													t_coord normal, double m);
t_coord					get_cone_normal(t_coord center, t_coord hit,
										t_coord normal, double k, double m);
int						read_scene(t_cont *c, char *path);
#endif