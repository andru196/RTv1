/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 00:59:52 by andru             #+#    #+#             */
/*   Updated: 2020/10/27 00:28:04 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						read_all_lines(const char *path, char ***ret, size_t *lines_num)
{
	char	*buf;
	int		fd;
	int		gnl;
	t_array	*rez;

	fd = open(path, O_RDONLY);
	if (fd >= 0)
	{
		rez = ft_array(1000);
		while ((gnl = get_next_line(fd, &buf)) > 0)
			ft_array_push(rez, buf);
		if (gnl >= 0)
		{
			*lines_num = rez->len;
			*ret = (char **)get_ptr_from_array(rez);
			return (1);
		}
	}
	return (0);
}

#define MAX_BUFF 5000

inline static int 		copy_data(t_list *lst[3], size_t size[2], char buf[MAX_BUFF + 1])
{
	if (!(lst[2] = ft_lstnew(buf, size[0])))
	{
		ft_lstdel_free(&lst[0]);
		return (0);
	}
	size[1] += size[0];
	if (!lst[0])
	{
		lst[0] = lst[2];
		lst[1] = lst[0];
	}
	else
	{
		lst[1]->next = lst[2];
		lst[1] = lst[1]->next;
	}
	return (1);
}

inline static int 		concat_data(char **ret, t_list *lst[3], size_t size[2])
{
	if (!(*ret = malloc(size[1] + 1)))
	{
		ft_lstdel_free(&lst[0]);
		return (0);
	}
	size[0] = 0;
	while (lst[0])
	{
		ft_memcpy(*ret + size[0], lst[0]->content, lst[0]->content_size);
		size[0] += lst[0]->content_size;
		lst[0] = lst[0]->next;
	}
	*((*ret)+ size[1]) = '\0';
	ft_lstdel_free(&lst[0]);
	return (1);
}

int						read_all_text(const char *path, char **ret)
{
	t_list	*lst[3];
	int		fd;
	size_t	size[2];
	char	buf[MAX_BUFF + 1];

	fd = open(path, O_RDONLY);
	if (fd >= 0)
	{
		ft_bzero(lst, sizeof(t_list*) * 2);
		size[1] = 0;
		while((size[0] = read(fd, buf, MAX_BUFF)) > 0)
			if (!copy_data(lst, size, buf))
				return (0);
		close(fd);
		return (concat_data(ret, lst, size));
	}
	return (0);
}
