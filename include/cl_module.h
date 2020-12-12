/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_module.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 00:28:52 by andru             #+#    #+#             */
/*   Updated: 2020/12/12 17:07:48 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_PARAMETR_H
# define CL_PARAMETR_H
# ifdef __APPLE__
#  include <OpenCL/cl.h>
#  include <OpenCL/cl_gl.h>
#  include <OpenCL/cl_gl_ext.h>
#  include <OpenCL/cl_ext.h>
# else
#  include <CL/cl.h>
# endif
# define MANDELBROT "mandelbrotProcess"
# define JULIA "juliaProcess"
# define BURNINGSHIP "burningShipProcess"
typedef struct s_platform   	t_platform_info;
typedef struct s_device     	t_device_info;
typedef struct s_clcomponents	t_clcomponents;

struct							s_clcomponents
{
	cl_device_id				device_id;
	cl_context					context;
	cl_command_queue			command_queue;
	cl_program					program;
	cl_kernel					kernel;
	cl_platform_id				platform_id;
	cl_uint						ret_num_devices;
	cl_uint						ret_num_platforms;
	cl_mem						buffer;
	cl_int						ret;
	char						*program_src;
	int							is_connected;
};

# include "rtv1.h"

struct							s_platform
{
	char						*profile;
	char						*version;
	char						*vendor;
	char						*extensions;
	char						*name;
};

struct							s_device
{
	t_llu						type;
	t_llu						vendor_id;
	t_llu						max_compute_units;
	t_llu						max_work_item_dimensions;
	t_llu						max_work_group_size;
	size_t						*max_work_item_size;
	cl_uint						address_bits;
	t_llu						local_mem_size;
	t_llu						global_mem_size;
	char						available;
	char						*name;
	char						*vendor;
	char						*version;
	char						*profile;
	char						*extensions;
	char						*platform;
};



int								cl_release_all(t_clcomponents *comp);
int								cl_read_img(t_clcomponents *comp, t_img *img);
// int								cl_try_init_connect(t_clcomponents *comp, char *filename);

#endif