/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 18:09:52 by ycorrupt          #+#    #+#             */
/*   Updated: 2020/10/25 20:58:38 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list *result;

	if ((result = (t_list *)malloc(sizeof(t_list))))
	{
		result->next = NULL;
		result->content = NULL;
		if (content == NULL)
			result->content_size = 0;
		else
		{
			if (!(result->content = ft_memalloc(content_size)))
			{
				free(result);
				return (NULL);
			}
			ft_memmove(result->content, (void *)content, content_size);
			result->content_size = content_size;
		}
	}
	return (result);
}

size_t		ft_lstcontsize(t_list *frst)
{
	size_t rez;

	rez = 0;
	while (frst)
	{
		rez += frst->content_size;
		frst = frst->next; 
	}
	return (rez);
}
