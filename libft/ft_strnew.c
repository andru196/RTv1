/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:30:48 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/02/05 19:17:46 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char				*str;
	unsigned long		i;

	if (!(str = (char *)malloc(size + 1)))
		return (NULL);
	else
	{
		i = 0;
		while (i <= size)
		{
			str[i] = '\0';
			i++;
		}
		return (str);
	}
}
