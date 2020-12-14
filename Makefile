# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andru <andru@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/07 17:08:37 by sfalia-f          #+#    #+#              #
#    Updated: 2020/12/14 19:59:40 by andru            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	rtv1
UNAME := $(shell uname)
DIR	=				./src/
FILES	=			main.c\
					image.c\
					events.c\
					free_cont.c\
					events_keyboard.c\
					events_mouse.c\
					test.c\
					t_coord_fun.c\
					figure_logic.c \
					shapes.c
					
SRCS			=	$(addprefix $(DIR), $(FILES))
OBJ				=	$(patsubst %.c, %.o, $(SRCS))
CC				=	clang
FLAGS			=	-g#-Wall -Wextra -Werror
LIBRARY			=	./libft/
LIBFT			=	$(LIBRARY)libft.a
HEADERS			=	include/ $(LIBRARY)includes
MINILIBDIR		=	minilib/
INCLUDES		=	-I include/ -I $(LIBRARY)includes -I $(MINILIBDIR)
ifeq ($(UNAME), Linux)
	LIBS = -lGL -lXext -lX11 -lm -lOpenCL -L $(MINILIBDIR) -lmlx
else
	LIBS = -lmlx -framework OpenGL -framework opencl -framework Appkit
endif

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L $(LIBRARY) -lft   $(LIBS)

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
