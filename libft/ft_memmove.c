/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 20:44:10 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/02/05 18:38:39 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_c;
	unsigned char	*src_c;
	size_t			temp;

	if (!len)
		return (dst);
	dst_c = (unsigned char *)dst;
	src_c = (unsigned char *)src;
	if (dst > src)
	{
		temp = len - 1;
		while (temp--)
		{
			++dst_c;
			++src_c;
		}
		while (len--)
			*dst_c-- = *src_c--;
	}
	else
		ft_memcpy(dst, src, len);
	return ((void *)dst);
}
