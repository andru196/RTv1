/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:24:22 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/02/22 21:22:20 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *result;
	t_list *temp;

	if (!lst || !f)
		return (NULL);
	result = f(lst);
	temp = result;
	lst = lst->next;
	while (lst)
	{
		if (!(temp->next = f(lst)))
			return (NULL);
		lst = lst->next;
		temp = temp->next;
	}
	return (result);
}
