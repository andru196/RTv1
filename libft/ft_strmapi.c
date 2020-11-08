/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:20:55 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/02/05 19:25:32 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				length;
	char			*result;
	unsigned int	i;

	if (s)
	{
		length = ft_strlen(s);
		if ((result = (char *)malloc(sizeof(char) * (length + 1))))
		{
			i = -1;
			while (s[++i])
				result[i] = f(i, s[i]);
			result[i] = '\0';
			return (result);
		}
	}
	return (NULL);
}
