/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 23:00:58 by andru             #+#    #+#             */
/*   Updated: 2020/12/18 01:46:59 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char		**split_line(char *str)
{
	char	*cpy;
	t_list	*lst[2];
	char	*tmp;
	int		i,j;
	char	**rez;
	
	ft_bzero(lst, sizeof(t_list *) * 2);
	cpy = str;
	while (*str)
	{
		if (*str == '{')
		{
			tmp = str;
			while (*str && *str != '}')
				str++;
			if (!lst[0])
			{
				lst[0] = ft_lstnew(tmp, str - tmp + 1);
				((char *)lst[0]->content)[lst[0]->content_size - 1] = '\0';
				lst[1] = lst[0];
			}
			else
			{
				lst[1]->next = ft_lstnew(tmp, str - tmp + 1);
				lst[1] = lst[1]->next;
				((char *)lst[1]->content)[lst[1]->content_size - 1] = '\0';
			}
		}
		else if (*str == ' ')
			while (*str && (*str == ' '))
				str++;
		else
		{
			tmp = str;
			while (*str && *str != ' ' && *str != '{')
				str++;
			if (!lst[0])
			{
				lst[0] = ft_lstnew(tmp, str - tmp + 1);
				((char *)lst[0]->content)[lst[0]->content_size - 1] = '\0';
				lst[1] = lst[0];
			}
			else
			{
				lst[1]->next = ft_lstnew(tmp, str - tmp + 1);
				lst[1] = lst[1]->next;
				((char *)lst[1]->content)[lst[1]->content_size - 1] = '\0';
			}
		}
	}
	lst[1] = lst[0];
	while (lst[1])
	{
		if (*(char *)lst[1]->content == '{')
		{
			tmp = lst[1]->content;
			lst[1]->content = ft_memalloc(sizeof(char **) * 2);
			*(char**)lst[1]->content = tmp;
			lst[1]->content_size = 1;
		}
		else
		{
			i = 0;
			tmp = lst[1]->content;
			lst[1]->content = ft_strsplit(tmp, ' ');
			free(tmp);
			while (((char **)lst[1]->content)[i])
				i++;
			lst[1]->content_size = i;
		}
		lst[1] = lst[1]->next;
	}
	i = ft_lstcontsize(lst[0]);
	rez = ft_memalloc(sizeof(char **) * (i + 1));
	
	lst[1] = lst[0];
	j = 0;
	while (lst[1])
	{
		lst[0] = lst[1];
		i = 0;
		while (i < lst[1]->content_size)
		{
			rez[j++] = ((char**)lst[1]->content)[i++];
		}
		free(lst[1]->content);
		lst[1] = lst[1]->next;
		free(lst[0]);
	}
	return (rez);
}

int main (int argc, char **argv)
{
	char *buf;
	char **rez;
	
	if (argc == 2)
	{
		int fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &buf) > 0)
		{
			//if (!rez && *buf != '#')
			{
				rez = split_line(buf);
				while (*rez)
				{
					printf("%s ", *rez++);
				}
			}
			printf("\n");
			free(buf);
		}
		close(fd);
	}
}

// static int	read_line(char *str, t_cont *c)
// {
	
// }

// /*
// ** Необходимо задать некий формат передаваемой сцены
// ** Пока сделаю самый простой:
// ** Имя_фигуры {координаты} [{Ещё координаты}] [всякие_радиусы_хуярусы] 0xЦВЕ7
// ** Коорднаты - это всегда 3 числа - выделим их фигурными скобками
// ** #комментарии
// */
// int			read_scene(t_cont *c, char *path)
// {
// 	int		fd;
// 	char	*buf;
// 	int		rez;

// 	fd = open(path, __O_DIRECTORY);
// 	if (fd != -1)
// 		print_errno(21, c);
// 	fd = open(path, O_RDONLY);
// 	if (fd == -1)
// 		print_errno(22, c);
// 	rez = 0;
// 	while (get_next_line(fd, &buf) > 0)
// 	{
// 		if (!rez && *buf != '#')
// 			rez = read_line(buf, c);
// 		free(buf);
// 	}
// 	close(fd);
// 	return (rez);
// }