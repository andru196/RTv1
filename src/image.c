/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:40:56 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/11/08 17:30:26 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_img	*new_image(void *mlx_ptr, int width, int height)
{
	t_img	*rez;

	rez = malloc(sizeof(t_img));
	if (rez)
	{
		rez->img_ptr = mlx_new_image(mlx_ptr, width, height);
		if (!rez->img_ptr)
		{
			free(rez);
			return (NULL);
		}
		rez->width = width;
		rez->height = height;
		rez->data = (byte *)(mlx_get_data_addr(rez->img_ptr,
			&rez->bits_per_pixel,
			&rez->size_line,
			&rez->endian));
	}
	return (rez);
}
