# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnails <cnails@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/20 12:57:53 by cnails            #+#    #+#              #
#    Updated: 2019/10/16 20:20:46 by cnails           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf

SRC= *.c

all: $(NAME)

$(NAME):
	gcc -I minilibx -L libft -lft -L minilibx -lmlx -framework OpenGL -framework AppKit ft_alg.c

valid:
	gcc -I minilibx -L libft -lft -L minilibx -lmlx -framework OpenGL -framework AppKit ft_valid.c

collect:
	gcc -I minilibx -L libft -lft -L minilibx -lmlx -framework OpenGL -framework AppKit ft_collect.c

clean:
	rm -f $(NAME)

re: clean all
