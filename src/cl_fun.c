/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_fun.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:44:20 by andru             #+#    #+#             */
/*   Updated: 2020/11/08 17:31:34 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			cl_release_all(t_clcomponents *comp)
{
	cl_int ret;

	ret = 0;
	if (comp->command_queue)
	{
		ret = clFlush(comp->command_queue);
		ret = clFinish(comp->command_queue);
		ret = clReleaseKernel(comp->kernel);
		ret = clReleaseProgram(comp->program);
		ret = clReleaseMemObject(comp->buffer);
		ret = clReleaseCommandQueue(comp->command_queue);
		ret = clReleaseContext(comp->context);
		comp->command_queue = NULL;
		comp->kernel = NULL;
		comp->program = NULL;
		comp->buffer = NULL;
		comp->context = NULL;
	if (ret >= 0)
		comp->is_connected = 0;
	}
	return (ret);
}

int			cl_read_img(t_clcomponents *comp, t_img *img)
{
	cl_int			ret;
	size_t const	global[] = {32, 32};
	size_t const	local[] = {(size_t) WIDTH, (size_t) HEIGHT};

	ret = clFlush(comp->command_queue);
	ret = clFinish(comp->command_queue);
	ret = clEnqueueNDRangeKernel(comp->command_queue, comp->kernel, 2, global,
												local, NULL, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(comp->command_queue, comp->buffer, CL_TRUE, 0,
							WIDTH * HEIGHT * sizeof(int), img->data, 0, NULL, NULL);
	return (!ret);
}

// int			cl_set_param(t_clcomponents *comp, t_fract fract, t_img *img, int is_extra)
// {
// 	unsigned	i;
// 	cl_int		ret;

// 	comp->buffer = clCreateBuffer(comp->context, CL_MEM_WRITE_ONLY,
// 					img->height * img->width * sizeof(cl_int4), NULL, &ret);
// 	i = 0;
// 	ret = clSetKernelArg(comp->kernel, i++, sizeof(cl_mem),
// 														(void *)&comp->buffer);
// 	ret = clSetKernelArg(comp->kernel, i++, sizeof(int), &img->width);
// 	ret = clSetKernelArg(comp->kernel, i++, sizeof(int), &img->height);
// 	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.min.re);
// 	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.min.im);
// 	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.max.re);
// 	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.max.im);
// 	ret = clSetKernelArg(comp->kernel, i++, sizeof(int), &fract.iteration);
// 	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.factor.re);
// 	ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.factor.im);
// 	if (is_extra)
// 	{
// 		ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.k.re);
// 		ret = clSetKernelArg(comp->kernel, i++, sizeof(double), &fract.k.im);	
// 	}
// 	return (!ret);
// }

// int			cl_try_init_connect(t_clcomponents *comp, char *filename)
// {
// 	size_t	source_size;
// 	cl_int	ret;

// 	if (comp->program_src || (ret = read_all_text(filename, &comp->program_src)))
// 	{
// 		ret = clGetPlatformIDs(1, &comp->platform_id, &comp->ret_num_platforms);
// 		ret = clGetDeviceIDs(comp->platform_id, CL_DEVICE_TYPE_GPU, 1, &comp->device_id, &comp->ret_num_devices);

// 		comp->context = clCreateContext(NULL, 1, &comp->device_id, NULL, NULL, &ret);
// 		comp->command_queue = clCreateCommandQueueWithProperties(comp->context, comp->device_id, 0, &ret);
// 		source_size = ft_strlen(comp->program_src);
// 		comp->program = clCreateProgramWithSource(comp->context, 1, (const char **)&comp->program_src,
// 								(const size_t *)&source_size, &ret);
// 		ret = clBuildProgram(comp->program, 1, &comp->device_id, NULL, NULL, NULL);
// 		if (set == mandelbrot_set)
// 			comp->kernel = clCreateKernel(comp->program, MANDELBROT, &ret);
// 		else if (set == julia_set)
// 			comp->kernel = clCreateKernel(comp->program, JULIA, &ret);
// 		else
// 			comp->kernel = clCreateKernel(comp->program, BURNINGSHIP, &ret);
// 		if (ret >= 0)
// 			comp->is_connected = 1;
// 	}
// 	return (ret);
// }
