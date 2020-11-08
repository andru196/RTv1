/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 14:52:41 by sfalia-f          #+#    #+#             */
/*   Updated: 2020/08/25 20:33:15 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(long long int n, int base)
{
	char				*result;
	unsigned long long	copy_n;
	int					r;

	copy_n = n < 0 && base == 10 ? ((ULL)-(LNGL)n) : (ULL)n;
	r = n < 0 && base == 10 ? 2 : 1;
	while (copy_n /= (base == 0 ? 10 : base))
		r++;
	if (!(result = (char *)malloc(sizeof(char) * (r + 1))))
		return (NULL);
	copy_n = n < 0 && base == 10 ? ((ULL)-(LNGL)n) : (ULL)n;
	if (n < 0 && base == 10)
		result[0] = '-';
	result[r] = '\0';
	result[0] = copy_n == 0 ? '0' : result[0];
	while (copy_n)
	{
		n = copy_n % (base == 0 ? 10 : base);
		result[r - 1] = n + (n > 9 ? 'a' - 10 : '0');
		--r;
		copy_n /= (base == 0 ? 10 : base);
	}
	return (result);
}
