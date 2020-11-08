/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 21:20:31 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/02/05 17:38:02 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	copy_s;
	size_t	len_dst;
	size_t	len_src;

	copy_s = size;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	dst += len_dst;
	size = len_dst > size ? 0 : size - len_dst;
	while (*src && size > 1)
	{
		--size;
		*dst++ = *src++;
	}
	*dst = '\0';
	return (copy_s > len_dst ? len_dst + len_src : len_src + copy_s);
}
