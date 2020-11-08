/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 22:07:19 by andru             #+#    #+#             */
/*   Updated: 2020/11/08 17:29:43 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	mouse_press(int button, int x, int y, void *param)
{
	t_cont		*c;

	return (1);
}

int	mouse_move(int x, int y, void *param)
{
	t_cont	*c;
	
	c = param;
	return (1);
}
