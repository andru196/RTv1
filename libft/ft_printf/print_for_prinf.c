/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_for_prinf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:26:45 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/07/02 17:24:03 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			print_c(t_param *lst, int *i, int fd)
{
	int k;

	if (!lst->str[0] || !lst->str[lst->width - 1])
		*i += !lst->str[0] ? lst->width : 1;
	k = -1;
	while (++k != lst->width)
		ft_putchar_fd(lst->str[k], fd);
}

static int			color(char *str, int *count, int fd)
{
	int j;

	j = !ft_strncmp(str, "{red}", 5) ? write(fd, "\033[31m", 5) : 0;
	j = !ft_strncmp(str, "{eoc}", 5) && !j ? write(fd, "\033[0m", 5) : j;
	j = !j && !ft_strncmp(str, "{black}", 7) ? write(fd, "\033[30m", 5) : j;
	j = !j && !ft_strncmp(str, "{green}", 7) ? write(fd, "\033[32m", 5) : j;
	j = !j && !ft_strncmp(str, "{yellow}", 8) ? write(fd, "\033[33m", 5) : j;
	j = !j && !ft_strncmp(str, "{blue}", 6) ? write(fd, "\033[34m", 5) : j;
	j = !j && !ft_strncmp(str, "{magenta}", 9) ? write(fd, "\033[35m", 5) : j;
	j = !j && !ft_strncmp(str, "{cyan}", 6) ? write(fd, "\033[36m", 5) : j;
	j = !j && !ft_strncmp(str, "{grey}", 6) ? write(fd, "\033[37m", 5) : j;
	j = !j && !ft_strncmp(str, "{white}", 7) ? write(fd, "\033[0m", 5) : j;
	*count += j ? j : 1;
	if (!j)
	{
		j++;
		ft_putchar_fd(*str, fd);
	}
	else
	{
		j = 1;
		while (*str++ != '}')
			j++;
	}
	return (j);
}

static int			ft_putmychar(char *str, int *i, int fd)
{
	int rez;
	int j;

	rez = 0;
	j = 0;
	while (*str != '%' && *str != '\0')
	{
		if (*str == '{')
		{
			j += color(str, i, fd);
			str += j;
		}
		else
		{
			ft_putchar_fd(*str++, fd);
			rez++;
		}
	}
	*i += rez;
	return (rez + j);
}

static int			change_fd(t_param **lst, int *fd)
{
	int tmp;

	if ((*lst)->type == 'q')
	{
		tmp = (int)(*lst)->param;
		if (tmp >= 0 && !write(tmp, "", 0))
			*fd = tmp;
		*lst = (*lst)->next ? (*lst)->next : *lst;
		return (1);
	}
	return (0);
}

int					print(char *str, t_param *lst)
{
	int i;
	int fd;

	i = 0;
	fd = 1;
	while (*str)
	{
		str += ft_putmychar(str, &i, fd);
		if (*str == '%')
		{
			str++;
			while (*str && ft_charinstr(".0987654321# -+lLh", *str))
				str++;
			str += *str ? 1 : 0;
			if (change_fd(&lst, &fd))
				continue ;
			i += ft_strlen(lst->str);
			if (lst->type != 'c')
				ft_putstr_fd(lst->str, fd);
			else
				print_c(lst, &i, fd);
			lst = lst ? lst->next : lst;
		}
	}
	return (i);
}
