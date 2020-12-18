/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 23:00:58 by andru             #+#    #+#             */
/*   Updated: 2020/12/18 14:35:38 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


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
			if (*str == '}')
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

int		get_fig_type(char *word)
{
	const char		*figs[] = FIGURES_NAMES;
	const size_t	figtype[] = FIGURES_TYPES;
	size_t			i;

	i = 0;
	while (figs[i])
	{
		if (!ft_strcmp(figs[i], word))
			return (figtype[i]);
		i++;
	}
	return (-1);
}

t_coord		get_coord(char *str)
{
	t_coord rez;

	ft_bzero(&rez, sizeof(t_coord));
	str++;
	rez.x = ft_atoi(str);
	while (*str != ' ' && *str)
		str++;
	while (*str == ' ' && *str)
		str++;
	rez.y = ft_atoi(str);
	while (*str != ' ' && *str)
		str++;
	while (*str == ' ' && *str)
		str++;
	rez.z = ft_atoi(str);
	return (rez);
}

static int	read_line(char *str, t_cont *c)
{
	char		**words;
	t_figure	cur;
	size_t		i;
	size_t		j;
	t_figlst	*fig;

	words = split_line(str);
	if (words[0] && (cur = get_fig_type(words[0])) >= 0 && cur < FIG_NUMS + 1)
	{
		i = 1;
		fig = init_figure(cur);
		add_fig(&c->figures, fig);
		j = 0;
		while (words[i])
		{
			if (*words[i] == '{' && j + sizeof(t_coord) < sizeof(t_gen_fig))
			{
				*(t_coord *)(((int8_t *)&fig->figure) + j) = get_coord(words[i]);
				j += sizeof(t_coord);
			}
			else if (*words[i] == '0' && (words[i][1] == 'X' || words[i][1] == 'x'))
			{
				int col = ft_atoix(words[i]);
				fig->mater.diffuse_color.x = (double)((col & 0xff0000) >> 16) / 255;
				fig->mater.diffuse_color.y = (double)((col & 0xff00) >> 8) / 255;
				fig->mater.diffuse_color.z = (double)((col & 0xff)) / 255;
			}
			else if (j + sizeof(double) < sizeof(t_gen_fig))
			{
				*(double *)(((int8_t *)&fig->figure) + j) = (double)ft_atoi(words[i]);
				j += sizeof(double);
			}
			i++;
		}
	}
	else if (words[0] && !ft_strcmp(words[0], LIGHT_NAME))
	{
		t_light rez;
		if (words[1] && words[2])
		{
			rez.position = get_coord(words[1]);
			rez.intensity = ((double)(ft_atoi(words[2]) % 100)) / 100;
		}
		else
			return (-1);
		ft_lstadd(&c->lights, ft_lstnew(&rez, sizeof(t_light)));
	}
	else
		return (-1);
	return (0);
}

/*
** Необходимо задать некий формат передаваемой сцены
** Пока сделаю самый простой:
** Имя_фигуры {координаты} [{Ещё координаты}] [всякие_радиусы_хуярусы] 0xЦВЕ7
** Коорднаты - это всегда 3 числа - выделим их фигурными скобками
** #комментарии
*/
int			read_scene(t_cont *c, char *path)
{
	int		fd;
	char	*buf;
	int		rez;

	fd = open(path, __O_DIRECTORY);
	if (fd != -1)
		print_errno(21, c);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		print_errno(22, c);
	rez = 0;
	while (get_next_line(fd, &buf) > 0)
	{
		if (!rez && *buf != '#')
			rez = read_line(buf, c);
		free(buf);
	}
	close(fd);
	return (rez);
}
