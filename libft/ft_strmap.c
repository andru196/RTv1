/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 16:28:11 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/02/05 19:23:28 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		length;
	char	*result;
	int		i;

	if (s)
	{
		length = ft_strlen(s);
		if ((result = (char *)malloc(sizeof(char) * (length + 1))))
		{
			i = -1;
			while (s[++i])
				result[i] = f(s[i]);
			result[i] = '\0';
			return (result);
		}
	}
	return (NULL);
}
