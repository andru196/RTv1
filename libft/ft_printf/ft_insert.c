/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 19:59:22 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/06/28 19:59:27 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_insert(char *where, char *what, size_t index)
{
	size_t	i;
	char	*str;

	i = 0;
	if (where)
		i += ft_strlen(where);
	if (index > i)
		return (NULL);
	if (what)
		i += ft_strlen(what);
	if (!(str = (char *)malloc(i)))
		return (NULL);
	ft_memcpy(str, where, index);
	str[index] = '\0';
	ft_strcat(str + index, what);
	ft_strcat(str, where + index);
	return (str);
}
