/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:13:55 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/06/26 19:14:55 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_charinstr(const char *str, char c)
{
	int i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] == c)
			return (1);
	return (0);
}

int			search_size(short int size[5])
{
	int i;

	i = -1;
	while (++i < 5)
		if (size[i])
			return (1);
	return (0);
}
