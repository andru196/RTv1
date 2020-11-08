/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 16:25:05 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/02/06 16:03:54 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*s1;
	char	*s2;
	int		length;

	s1 = (char *)haystack;
	s2 = (char *)needle;
	length = ft_strlen(s2);
	if (!*s2)
		return (s1);
	while (*s1 && (long int)len - length + 1 > 0)
	{
		if (!(ft_strncmp(s1, s2, length)))
			return (s1);
		--len;
		++s1;
	}
	return (NULL);
}
