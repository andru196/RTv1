/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 15:18:36 by ycorrupt          #+#    #+#             */
/*   Updated: 2018/12/27 12:48:57 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		length;
	char	*result;

	result = (char *)s;
	while (*result)
		result++;
	length = ft_strlen(s) + 1;
	while (length--)
	{
		if (*result-- == (char)c)
			return (++result);
	}
	return (NULL);
}
