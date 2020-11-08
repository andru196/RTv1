/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searching.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 14:50:02 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/06/26 21:43:12 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		check(const char **str, short int el[5], char const *const f[])
{
	int		i;

	i = 0;
	while (f[i])
	{
		if (ft_strncmp(*str, f[i], ft_strlen(f[i])) == 0)
		{
			if (el[i] == 0)
			{
				el[i] = (short int)1;
				*str += ft_strlen(f[i]);
				return (1);
			}
			*str += 1;
			return (1);
		}
		++i;
	}
	return (0);
}

static int		width(const char **str, int *el)
{
	if (ft_isdigit(**str) && **str != '0')
	{
		*el = ft_atoi(*str);
		while (ft_isdigit(**str))
			*str += 1;
		return (1);
	}
	return (0);
}

static int		prec(const char **str, int *el)
{
	if (**str == '.')
	{
		*str += 1;
		*el = 0;
		if (ft_isdigit(**str))
		{
			*el = ft_atoi(*str);
			while (ft_isdigit(**str))
				*str += 1;
		}
		return (1);
	}
	return (0);
}

static t_param	*addparam(t_param **start, t_list **ml)
{
	t_param	*tmp;
	t_param	*result;

	if ((result = (t_param *)sm(malloc(sizeof(t_param)), ml, 1)))
	{
		result->next = NULL;
		ft_bzero(result->flag, 10);
		result->width = 0;
		result->precision = -1;
		ft_bzero(result->size, 10);
		result->type = 0;
		result->str = NULL;
		result->param = NULL;
	}
	if (*start == NULL)
		*start = result;
	else
	{
		tmp = *start;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = result;
	}
	return (result);
}

t_param			*searching(const char *str, t_list **ml)
{
	t_param				*start;
	t_param				*el;
	char const *const	s[] = {"hh", "h", "ll", "l", "L", NULL};
	char const *const	f[] = {"+", "-", "#", " ", "0", NULL};

	start = NULL;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			++str;
			el = addparam(&start, ml);
			while (*str != '\0')
			{
				if (!(check(&str, el->size, s)) && !(check(&str, el->flag, f))
				&& !(width(&str, &el->width)) && !(prec(&str, &el->precision)))
				{
					el->type = *str;
					break ;
				}
			}
		}
		str += *str ? 1 : 0;
	}
	return (start);
}
