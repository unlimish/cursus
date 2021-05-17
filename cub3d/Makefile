CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCS = ./inc/
SRCS = src/main.c

MINILIB_X = minilibx-linux/libmlx.a -lXext -lX11 -lm

main:
	$(CC) $(SRCS) -I$(INCS) -I./minilibx-linux $(MINILIB_X) && ./a.out
addr:
	$(CC) -fsanitize=address $(SRCS) -I$(INCS) $(MINILIB_X) && ./a.out

%.o: %.c
	$(CC) -Wall  -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
