/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andru <andru@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 14:31:06 by ycorrupt          #+#    #+#             */
/*   Updated: 2020/10/21 01:17:56 by andru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>
# define UND unsigned
# define UC unsigned char
# define US unsigned short
# define UL unsigned long
# define ULL unsigned long long
# define LL long long
# define LD long double
# define doubleS "eEfFgG"
# define INTS "diouxXb"

typedef struct		s_param
{
	short int			flag[5];
	int					width;
	int					precision;
	short int			size[5];
	char				type;
	char				*str;
	void				*param;
	struct s_param		*next;
}					t_param;

int					ft_printf(const char *format, ...);
t_param				*searching(const char *str, t_list **ml);
t_param				*size_revision(t_param *params);
void				check_flags(t_param *el, t_list **ml);
int					convert_param(t_param *lst, va_list factor, t_list **ml);
int					makestr_di(t_param *lst, t_list **ml);
int					makestr_oux(t_param *lst, t_list **ml);
int					precision_dioux(t_param *lst, t_list **ml);
void				makestr_csp(t_param *lst, t_list **ml);
int					makestr_f(t_param *lst, t_list **ml);
int					search_size(short int size[5]);
char				*ft_dtoa(long double nbr);
int					ft_charinstr(const char *str, char c);
void				lst_killer(t_param **lst);
int					print(char *str, t_param *lst);
int					makestr_e(t_param *lst, t_list **ml);
char				*ft_insert(char *where, char *what, size_t index);
void				g_edit(t_param *lst, t_list **ml);
int					pr_f(t_param *lst, t_list **ml);
void				*sm(void *content, t_list **lst, int code);
void				exit_pf(t_list *lst, int code);
void				del_lst(t_list **lst, int from_end, int ex);
void				del_win(t_list **lst, void *content);

#endif
