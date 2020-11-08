/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 00:40:44 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/11/08 17:28:59 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "keys.h"

static void	ext(t_cont *c)
{
	free_cont(c);
	ft_putendl("Bye, bye.....");
	exit(0);
}
int 		key_press(int keycode, void *param)
{
	t_cont *c;

	c = (t_cont*)param;
	if (NUM_Q == keycode || keycode == NUM_ESC)
		ext(c);
	return (1);
}
