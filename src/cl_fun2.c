/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_fun2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:58:21 by andru             #+#    #+#             */
/*   Updated: 2020/11/08 17:27:42 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_module.h"

t_platform_info		*get_platform_info(cl_platform_id id)
{
    t_platform_info	*rez;
    size_t			size;

    rez = malloc(sizeof(t_platform_info));
    clGetPlatformInfo(id, CL_PLATFORM_PROFILE, 0, 0, &size);
    clGetPlatformInfo(id, CL_PLATFORM_PROFILE, size, (rez->profile = malloc(size)), &size);
    clGetPlatformInfo(id, CL_PLATFORM_VERSION, 0, 0, &size);
    clGetPlatformInfo(id, CL_PLATFORM_VERSION, size, (rez->version = malloc(size)), &size);
    clGetPlatformInfo(id, CL_PLATFORM_VENDOR, 0, 0, &size);
    clGetPlatformInfo(id, CL_PLATFORM_VENDOR, size, (rez->vendor = malloc(size)), &size);
    clGetPlatformInfo(id, CL_PLATFORM_EXTENSIONS, 0, 0, &size);
    clGetPlatformInfo(id, CL_PLATFORM_EXTENSIONS, size, (rez->extensions = malloc(size)), &size);
    clGetPlatformInfo(id, CL_PLATFORM_NAME, 0, 0, &size);
    clGetPlatformInfo(id, CL_PLATFORM_NAME, size, (rez->name = malloc(size)), &size);
	return rez;
}

static inline t_device_info		*get_device_part2(t_device_info *rez, size_t size, cl_device_id id)
{	
	clGetDeviceInfo(id, CL_DEVICE_NAME, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_NAME, size, rez->name = malloc(size), &size);
	clGetDeviceInfo(id, CL_DEVICE_VENDOR, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_VENDOR, size, rez->vendor = malloc(size),
																		&size);
	clGetDeviceInfo(id, CL_DEVICE_VERSION, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_VERSION, size, rez->version = malloc(size),
																		&size);
	clGetDeviceInfo(id, CL_DEVICE_PROFILE, 0, 0, &size);	
	clGetDeviceInfo(id, CL_DEVICE_PROFILE, size, rez->profile = malloc(size),
																		&size);
	clGetDeviceInfo(id, CL_DEVICE_EXTENSIONS, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_EXTENSIONS, size,
										rez->extensions = malloc(size), &size);
	clGetDeviceInfo(id, CL_DEVICE_PLATFORM, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_PLATFORM, size, rez->platform = malloc(size),
																		&size);
	clGetDeviceInfo(id, CL_DEVICE_LOCAL_MEM_SIZE, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_LOCAL_MEM_SIZE, size, &rez->local_mem_size,
																		&size);
	clGetDeviceInfo(id, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, size,
												&rez->global_mem_size, &size);
	clGetDeviceInfo(id, CL_DEVICE_AVAILABLE, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_AVAILABLE, size, &rez->available, &size);
	return (rez);
}

t_device_info   *get_device_info(cl_device_id id)
{
    t_device_info	*rez;
    size_t			size;

	rez = malloc(sizeof(t_device_info));
	clGetDeviceInfo(id, CL_DEVICE_TYPE, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_TYPE, sizeof(t_llu), &rez->type, &size);
	clGetDeviceInfo(id, CL_DEVICE_VENDOR_ID, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_VENDOR_ID, sizeof(t_llu), &rez->vendor_id,
		&size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_COMPUTE_UNITS, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(t_llu),
		&rez->max_compute_units, &size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(t_llu),
										&rez->max_work_item_dimensions, &size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_GROUP_SIZE, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(t_llu),
											&rez->max_work_group_size, &size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_ITEM_SIZES, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_MAX_WORK_ITEM_SIZES, size,
						rez->max_work_item_size = malloc(size), &size);
	clGetDeviceInfo(id, CL_DEVICE_ADDRESS_BITS, 0, 0, &size);
	clGetDeviceInfo(id, CL_DEVICE_ADDRESS_BITS, sizeof(cl_uint),
													&rez->address_bits, &size);
	return get_device_part2(rez, size, id);
}
