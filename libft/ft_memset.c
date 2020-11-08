/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:40:12 by ycorrupt          #+#    #+#             */
/*   Updated: 2020/08/25 21:41:44 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


static void		in_small_string(void *s, UC c, size_t *n)
{
	while (*n != 0)
	{
		*(UC *)s = c;
		*n -= 1;
		s++;
	}
}

static void		*ft_memsync(void *s, UC c, size_t *n)
{
	while (((size_t)s & (sizeof(size_t) - 1)) != 0)
	{
		*(UC *)s = c;
		*n -= 1;
		s++;
	}
	return (s);
}

void			*ft_memset(void *b, int c, size_t len)
{
	size_t			*bogey;
	size_t			num;
	size_t			ver;
	UC				symb;

	symb = (UC)c;
	ver = sizeof(size_t);
	num = c;
	bogey = (size_t *)b;
	if (0 == len)
		return (b);
	if (len < sizeof(size_t))
	{
		in_small_string((void *)bogey, symb, &len);
		return (b);
	}
	while (ver-- != 0)
		num = ((num) << 8) + (int)symb;
	bogey = ft_memsync((void *)bogey, symb, &len);
	ver = len / sizeof(size_t);
	while (ver-- != 0)
		*bogey++ = num;
	ver = len % sizeof(size_t);
	in_small_string((void *)bogey, symb, &ver);
	return (b);
}
