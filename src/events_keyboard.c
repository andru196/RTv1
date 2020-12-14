/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 00:40:44 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/12/14 21:44:09 by andru            ###   ########.fr       */
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

void		change_orig(t_cont *c, int keycode, t_coord *orig)
{
	if (keycode == DOWN_KEY && c->pressed_keys.shift)
		orig->z += 1;
	else if (keycode == DOWN_KEY)
		orig->y -= 1;
	else if (keycode == UP_KEY && c->pressed_keys.shift)
		orig->z -= 1;
	else if (keycode == UP_KEY)
		orig->y += 1;
	else if (keycode == LEFT_KEY)
		orig->x -= 1;
	else if (keycode == RIGHT_KEY)
		orig->x += 1;
	render(c->figures, (int *)c->img->data, c->lights, *orig);
	mlx_put_image_to_window(c->mlx_ptr, c->mlx_win, c->img->img_ptr, 0, 0);
}

static inline void	set_press_key(int keycode, t_cont *c)
{
	if (keycode == LSFT_KEY || keycode == RSFT_KEY)
		c->pressed_keys.shift = 1;
	else if (keycode == TAB_KEY)
		c->pressed_keys.tab = 1;
	else if (keycode == LCMD_KEY || keycode == RCMD_KEY)
		c->pressed_keys.ctrl = 1;
	else if (keycode == LOPT_KEY || keycode == ROPT_KEY)
		c->pressed_keys.alt = 1;
}

int 		key_press(int keycode, void *param)
{
	t_cont			*c;
	static t_coord	orig = {0.1, 0.1, 0.1};

	c = (t_cont*)param;
	set_press_key(keycode, param);
	if (NUM_Q == keycode || keycode == NUM_ESC)
		ext(c);
	else if (keycode == DOWN_KEY || keycode == UP_KEY || keycode == LEFT_KEY
														|| keycode == RIGHT_KEY)
		change_orig(c, keycode, &orig);
	return (1);
}

int key_release(int keycode, void *param)
{
	t_cont			*c;

	c = (t_cont*)param;
	if (keycode == LSFT_KEY || keycode == RSFT_KEY)
		c->pressed_keys.shift = 0;
	else if (keycode == TAB_KEY)
		c->pressed_keys.tab = 0;
	else if (keycode == LCMD_KEY || keycode == RCMD_KEY)
		c->pressed_keys.ctrl = 0;
	else if (keycode == LOPT_KEY || keycode == ROPT_KEY)
		c->pressed_keys.alt = 0;
	return (1);
}

