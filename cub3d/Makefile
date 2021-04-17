CC = gcc

CFLAGS = -Wall -Wextra -Werror

main:
	$(CC) src/main.c ./minilibx-linux/libmlx.a -lXext -lX11 && ./a.out

%.o: %.c
	$(CC) -Wall  -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
