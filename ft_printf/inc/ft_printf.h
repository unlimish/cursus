#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define END_OF_DOT -2
# define INIT -1

typedef struct	s_flag
{
	bool	flg_minus;
	bool	flg_zero;
	bool	is_nega;
	bool	acc_nega_aster;
	int		field;
	int		acc;
	int		conv_spec;
	int		zero_len;
	int		field_len;
	int		va_len;
}				t_flag;

int				ft_printf(const char *fmt, ...);

char			*ft_strchr(const char *s, int c);
int				ft_putstr_len(const char **start, const char **fmt);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *str);
int				ft_atoi(const char *nptr);
int				ft_isspace(char c);

#endif
