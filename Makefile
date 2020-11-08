# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andru <andru@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/07 17:08:37 by sfalia-f          #+#    #+#              #
#    Updated: 2020/11/01 22:13:34 by andru            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	fractol
DIR	=				./src/
FILES	=			main.c\
					image.c\
					events.c\
					complex.c\
					free_cont.c\
					events_keyboard.c\
					events_mouse.c\
					cl_fun.c cl_fun2.c\
					fractol_default.c\
					process_multy_thread.c\
					process_single_thread.c\
					formulas.c
SRCS			=	$(addprefix $(DIR), $(FILES))
OBJ				=	$(patsubst %.c, %.o, $(SRCS))
CC				=	clang
FLAGS			=	-Wall -Wextra -Werror
LIBRARY			=	./libft/
LIBFT			=	$(LIBRARY)libft.a
HEADERS			=	include/ $(LIBRARY)includes
MINILIBDIR		=	minilib/
INCLUDES		=	-I include/ -I $(LIBRARY)includes -I $(MINILIBDIR)
LIBS = -lGL -lXext -lX11 -lm -lOpenCL
all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC)  $(FLAGS) -o $(NAME) $(OBJ) -L $(LIBRARY) -lft -L $(MINILIBDIR) -lmlx  $(LIBS)

$(LIBFT):
	make -C $(LIBRARY)

%.o : %.c $(HEADERS)
	$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBRARY) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBRARY) fclean

re: fclean all
