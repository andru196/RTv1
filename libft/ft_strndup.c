/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 19:36:05 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/02/22 20:00:36 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char		*result;
	size_t		size;
	char		*temp;

	temp = NULL;
	if (n == 0)
		temp = ft_strnew(0);
	if (n > 0)
	{
		size = ft_strlen(s1);
		if ((result = ft_strnew(n > size ? size : n)))
		{
			temp = result;
			while (*s1 && n--)
				*result++ = *s1++;
		}
	}
	return (temp);
}
