/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:06:38 by ycorrupt          #+#    #+#             */
/*   Updated: 2018/12/16 19:37:10 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *result;

	result = (unsigned char *)s;
	while (n--)
	{
		if (*result++ == (unsigned char)c)
			return ((void *)(--result));
	}
	return (NULL);
}
