/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 19:58:47 by ycorrupt          #+#    #+#             */
/*   Updated: 2018/12/16 19:37:05 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *dst_c;
	unsigned char *src_c;

	dst_c = (unsigned char *)dst;
	src_c = (unsigned char *)src;
	while (n--)
	{
		*dst_c++ = *src_c++;
		if (*(src_c - 1) == (unsigned char)c)
			return (dst_c);
	}
	return (NULL);
}
