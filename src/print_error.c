/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 23:18:23 by andru             #+#    #+#             */
/*   Updated: 2020/12/17 23:18:49 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	print_errno(int errnom, t_cont *c)
{
	perror(strerror(errnom));
	free_cont(c);
	exit(1);
}

void	print_error(char *error, t_cont *c)
{
	ft_putendl(error);
	free_cont(c);
	exit(1);
}