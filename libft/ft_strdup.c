/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:05:00 by ycorrupt          #+#    #+#             */
/*   Updated: 2018/12/16 19:49:00 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*dup;
	size_t		i;

	i = ft_strlen(s1);
	if (!(dup = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	else
	{
		dup[i] = '\0';
		while (i--)
			dup[i] = s1[i];
		return (dup);
	}
}
