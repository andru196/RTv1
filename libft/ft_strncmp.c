/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 18:42:23 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/02/06 15:50:32 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n != 0 && s1 != s2)
	{
		while (*s1 == *s2 && *s1 && *s2 && n - 1)
		{
			++s1;
			++s2;
			--n;
		}
		return ((unsigned char)*s1 - (unsigned char)*s2);
	}
	return (0);
}
