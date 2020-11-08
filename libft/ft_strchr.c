/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 21:25:59 by ycorrupt          #+#    #+#             */
/*   Updated: 2018/12/22 15:25:06 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		length;
	char	*result;

	result = (char *)s;
	length = ft_strlen(s) + 1;
	while (length--)
	{
		if (*result++ == (char)c)
			return (--result);
	}
	return (NULL);
}
