NAME = fdf

all: $(NAME)

$(NAME):
	cc -I /usr/local/include/ main.c ft_collect.c -L libft -lft -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

clean:
	rm -f fdf
