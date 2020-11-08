/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 12:56:44 by ycorrupt          #+#    #+#             */
/*   Updated: 2019/02/06 17:04:03 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		words(char const *s, char c)
{
	int result;

	result = (*s == c || !*s) ? 0 : 1;
	while (*s)
	{
		if (*s == c && *(s + 1) != c)
			++result;
		++s;
	}
	if (*(s - 1) == c)
		--result;
	return (result);
}

static char		**error_case(char ***result, int i)
{
	while (i--)
		free(*result[i]);
	free(*result);
	*result = NULL;
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**result;
	int			i;
	char const	*temp;

	i = -1;
	if (!s)
		return (NULL);
	if (!(result = (char **)malloc(sizeof(char *) * (words(s, c) + 1))))
		return (NULL);
	result[words(s, c)] = NULL;
	temp = *s == c ? NULL : s;
	while (*s)
	{
		if (*s == c && *(s + 1) != c)
			temp = s + 1;
		else if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
		{
			if ((result[++i] = ft_strnew(s - temp + 1)))
				result[i] = ft_strncpy(result[i], temp, s - temp + 1);
			else
				return (error_case(&result, i));
		}
		++s;
	}
	return (result);
}
