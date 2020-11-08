/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 19:08:24 by ycorrupt          #+#    #+#             */
/*   Updated: 2018/12/27 15:15:32 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *p_dst;

	p_dst = dst;
	while (*src && len)
	{
		*dst++ = *src++;
		--len;
	}
	while (len--)
		*dst++ = '\0';
	return (p_dst);
}
