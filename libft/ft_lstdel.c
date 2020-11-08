/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 18:55:38 by ycorrupt          #+#    #+#             */
/*   Updated: 2020/10/26 23:43:58 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *temp;

	while ((*alst))
	{
		temp = (*alst)->next;
		ft_lstdelone(alst, del);
		(*alst) = temp;
	}
}

void	ft_lstdel_free(t_list **alst)
{
	t_list *temp;

	while ((*alst))
	{
		temp = (*alst)->next;
		free((*alst)->content);
		ft_memdel((void **)alst);
		(*alst) = temp;
	}
}
