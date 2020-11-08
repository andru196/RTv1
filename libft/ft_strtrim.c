/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 15:54:31 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/02/05 19:38:10 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*result;
	char	*copy_s;
	int		length;

	if (s)
	{
		length = 1;
		while (*s == ' ' || *s == '\n' || *s == '\t')
			++s;
		if (!*s)
			return (ft_strnew(0));
		copy_s = (char *)s;
		while (*s)
			++s;
		while (*s == ' ' || *s == '\n' || *s == '\t' || *s == '\0')
			--s;
		while (s-- != copy_s)
			++length;
		if (!(result = (char *)malloc(sizeof(char) * (length + 1))))
			return (NULL);
		result[length] = '\0';
		return (ft_strncpy(result, copy_s, length));
	}
	return (NULL);
}
