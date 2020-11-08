/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 15:25:50 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/03/06 21:17:12 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *result;

	if (s1 && s2)
	{
		if ((result = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		{
			ft_strcat(result, s1);
			ft_strcat(result, s2);
			return (result);
		}
	}
	else if (!s1 && s2)
		return (ft_strdup(s2));
	else if (s1 && !s2)
		return (ft_strdup(s1));
	return (NULL);
}
