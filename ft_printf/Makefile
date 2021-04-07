NAME = libftprintf.a

SRCS =	src/ft_printf.c \
		src/print.c \
		src/print_str.c \
		src/print_percent.c \
		src/print_u.c \
		src/print_hex.c \
		src/proc_fmt.c \
		src/init_flags.c \
		src/print_ptr.c \
		src/print_int.c \
		src/utils/utils.c \
		src/utils/ft_itoa.c \
		src/utils/ft_utoa.c \
		src/utils/ft_strcpy.c \
		src/utils/ft_dechex.c \
		src/utils/utils_write.c \
		src/utils/ft_toupper.c \
		src/utils/ft_strlcat.c \
		src/utils/ft_strjoin.c \
		src/utils/ft_memcpy.c \
		src/utils/ft_atoi.c


OBJ = $(SRCS:.c=.o)

HEADER =	inc/ft_printf.h \
			inc/print.h \
			inc/proc_fmt.h \
			inc/utils.h

CC = gcc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

%.o:%.c
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)
		ar -s $(NAME)

# so: libft.so

# libft.so: $(OBJ)
# 		$(CC) -shared -fPIC -o libft.so $(OBJ)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: re clean fclean all
