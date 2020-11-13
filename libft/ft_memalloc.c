/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:06:55 by ycorrupt          #+#    #+#             */
/*   Updated: 2020/11/13 22:33:30 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *result;

	if (size > 0)
	{
		result = (void *)malloc(size);
		if (result)
		{
			ft_bzero(result, size);
			return (result);
		}
	}
	return (NULL);
}
