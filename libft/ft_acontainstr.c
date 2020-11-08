/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_acontainstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 00:50:39 by andru             #+#    #+#             */
/*   Updated: 2020/10/29 01:01:35 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_acontainstr(char *str, char **arr, size_t arrlenth)
{
	size_t	i;

	i = 0;
	while (i < arrlenth)
		if (!ft_strcmp(str, arr[i++]))
			return (i);
	return (0);
}
