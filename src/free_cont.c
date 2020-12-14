/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cont.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 01:04:41 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/12/14 21:09:44 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	free_cont(t_cont *c)
{
	if (c)
	{
		if (c->img)
		{
			if (c->img->data)
				mlx_destroy_image(c->mlx_ptr, c->img->img_ptr);
			ft_memdel((void **)&c->img);
		}
		if (c->mlx_win)
			mlx_destroy_window(c->mlx_ptr, c->mlx_win);
		if (c->mlx_ptr)
			free((void *)c->mlx_ptr);
	}
}
