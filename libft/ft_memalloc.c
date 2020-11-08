/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:06:55 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/02/05 19:13:22 by ycorrupt         ###   ########.fr       */
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
