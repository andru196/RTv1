# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andru <andru@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/05 17:33:42 by ycorrupt          #+#    #+#              #
#    Updated: 2020/10/29 00:53:38 by andru            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS1 = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c \
ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c \
ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c ft_strnew.c \
ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c read_file.c ft_acontainstr.c\
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_memchr.c ft_swap.c ft_mod.c ft_array.c ft_atoix.c ft_isspace.c\
ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_pow.c ft_isupper.c ft_islower.c ft_itoa_base.c \
ft_strcapitalize.c ft_strndup.c get_next_line.c ft_utoa.c ft_mult.c ft_power_for_two.c ft_mult_atod.c ft_lstlen.c ft_lstladd.c
SRCS2 = ./ft_printf/csp.c ./ft_printf/dioux.c ./ft_printf/f.c ./ft_printf/flags.c ./ft_printf/ft_dtoa.c ./ft_printf/print.c ./ft_printf/searching.c \
./ft_printf/size_converter.c ./ft_printf/size_revision.c ./ft_printf/lst_killer.c ./ft_printf/help.c  ft_printf/e.c ft_printf/ft_insert.c ft_printf/g.c ft_printf/print_for_prinf.c
OBJ1 = $(SRCS1:.c=.o)
OBJ2 = csp.o dioux.o f.o flags.o ft_dtoa.o print.o searching.o size_converter.o e.o g.o size_revision.o lst_killer.o help.o ft_insert.o print_for_prinf.o
OBJ = $(OBJ1) $(OBJ2)
HEADER = ./includes
CC = clang
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(OBJ):
	@$(CC) -I $(HEADER) $(FLAGS) -c $(SRCS1)
	@$(CC) -I $(HEADER) $(FLAGS) -c $(SRCS2)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all