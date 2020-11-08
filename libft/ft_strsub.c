/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 19:45:59 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/02/06 22:18:21 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		length;
	char	*result;

	if (s)
	{
		length = ft_strlen(s);
		length = length - start > (long int)len ?
				(long int)len : length - start;
		if ((result = (char *)malloc(sizeof(char) * (length + 1))))
		{
			ft_strncpy(result, s + start, length);
			result[length] = '\0';
			return (result);
		}
	}
	return (NULL);
}
