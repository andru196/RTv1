/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 22:03:58 by andru             #+#    #+#             */
/*   Updated: 2020/11/08 17:28:22 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H
# include "rtv1.h"

void        lr_mouse_press(int button, int x, int y, t_cont *c);
int     	mouse_press(int button, int x, int y, void *param);
int     	mouse_release(int button, int x, int y, void *param);
int     	mouse_move(int x, int y, void *param);
int         key_press(int keycode, void *param);

# endif