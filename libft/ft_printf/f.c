/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 21:24:12 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/10/21 01:17:56 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_exception(char **l_str, char *str, t_list **ml)
{
	char *cpy;

	cpy = *l_str;
	if ((cpy == str && *str == ':') || ((cpy + 1) == str && *cpy == '-'))
	{
		*str = '0';
		*l_str = sm(ft_insert(cpy, "1", *(cpy) == '-'), ml, 0);
		del_win(ml, cpy);
		return (1);
	}
	else if (ft_charinstr("+-", *str - 1) && str != cpy)
	{
		*(str + 1) = '\0';
		str = sm(ft_strjoin(cpy, "100"), ml, 0);
		del_win(ml, cpy);
		*l_str = str;
		return (1);
	}
	return (0);
}

static int	check_double(t_param *lst, t_list **ml)
{
	char	*str;
	char	*cpy;

	cpy = lst->str;
	str = lst->str;
	while (*(str + 1))
		str++;
	while (*str == ':' || *str == '/')
	{
		if (check_exception(&lst->str, str, ml))
			break ;
		*str = *str == ':' ? '0' : '9';
		if (*--str == '.')
			str--;
		*str += *(str + 1) == '0' ? 1 : -1;
	}
	if (ft_charinstr("eE", lst->type) && *str == '0' &&
		*(str - 1) == '0' && *(str - 2) == '-')
		*(str - 2) = '+';
	return (0);
}

int			pr_f(t_param *lst, t_list **ml)
{
	int		i;
	char	*str;
	char	*str2;

	str = lst->str;
	while (*str && *str++ != '.')
		i = (!lst->precision && *str) ? 1 : lst->precision;
	i += (!*str && lst->precision) - (!lst->precision &&
									!ft_strcmp(str - 1, "."));
	while (ft_charinstr("0987654321", *str) && --i > 0)
		str++;
	str -= lst->precision == 0;
	ft_memset((str2 = sm(ft_strnew(i), ml, 0)), '0', i);
	*str2 = !ft_strchr(lst->str, '.') ? '.' : *str2;
	if (*(str + 1) >= '5' && *str != '.')
		*str += 1;
	else if (*(str + 1) >= '5')
		*(str - 1) += 1;
	*str = *str == '.' ? '\0' : *str;
	str = sm(ft_strsub(lst->str, 0, str - lst->str + 1 - (*str == '.')), ml, 0);
	del_win(ml, lst->str);
	lst->str = sm(ft_strjoin(str, str2), ml, 0);
	del_lst(ml, 3, 0);
	return (check_double(lst, ml));
}

static int	pr_e(t_param *lst, t_list **ml)
{
	char	*str1;
	char	*str;

	str = lst->str;
	while (*str != 'e' && *str != 'E')
		str++;
	str1 = sm(ft_strsub(str, 0, ft_strlen(str)), ml, 0);
	*str = '\0';
	pr_f(lst, ml);
	str = lst->str + (*lst->str == '-');
	if (*(long double *)lst->param != 0.0 && ft_strlen(str) != (size_t)(1 +
		!(lst->precision == 0) + (*str == '-') + lst->precision))
	{
		*(str + 1) = ft_strlen(str) > 1 ? '.' : '\0';
		*(str + 2) = ft_strlen(str) > 2 ? '0' : '\0';
		pr_f(lst, ml);
		str = lst->str;
		str1[ft_strlen(str1) - 1] += ft_atoi(str1 + 1) <= -1 ? -1 : 1;
	}
	str = sm(ft_strjoin(lst->str, str1), ml, 0);
	del_lst(ml, 3, 0);
	lst->str = str;
	check_double(lst, ml);
	return (0);
}

int			makestr_f(t_param *lst, t_list **ml)
{
	char *str;

	if (lst->size[4])
		lst->str = sm(ft_dtoa((LD)*((LD *)(lst->param))), ml, 0);
	else if (lst->size[3])
		lst->str = sm(ft_dtoa((LD)*((double *)(lst->param))), ml, 0);
	else
		lst->str = sm(ft_dtoa((LD)*((double *)(lst->param))), ml, 0);
	g_edit(lst, ml);
	lst->precision = lst->precision == -1 ? 6 : lst->precision;
	if ((lst->type == 'e' || lst->type == 'E') && 'i' != lst->str[1]
		&& ft_charinstr("0987654321-", *lst->str))
		if (makestr_e(lst, ml))
			return (1);
	if (ft_charinstr("FEG", lst->type))
	{
		str = lst->str - 1;
		while (*++str)
			*str = ft_toupper(*str);
	}
	if (ft_isdigit(lst->str[0]) || ft_isdigit(lst->str[1]))
		return (ft_charinstr("Ff", lst->type) ? pr_f(lst, ml) : pr_e(lst, ml));
	return (0);
}
