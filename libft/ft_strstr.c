/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 15:25:39 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/02/05 18:49:08 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcmpmod(const char *haystack, const char *needle)
{
	char *s1;
	char *s2;

	s1 = (char *)haystack;
	s2 = (char *)needle;
	while (*s1 == *s2 && *s1 && *s2)
	{
		if (!(*(s2 + 1)))
			return (1);
		s1++;
		s2++;
	}
	if (!(*s1) && !(*s2))
		return (1);
	return (0);
}

char		*ft_strstr(const char *haystack, const char *needle)
{
	char *s1;
	char *s2;

	s1 = (char *)haystack;
	s2 = (char *)needle;
	if (!*s2)
		return (s1);
	while (*s1)
	{
		if (ft_strcmpmod(s1, s2))
			return (s1);
		++s1;
	}
	return (NULL);
}
