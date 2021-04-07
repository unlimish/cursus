#ifndef PRINT_H
# define PRINT_H

# include "ft_printf.h"

int				print_format(t_flag *flags, va_list args);
int				prt_percent(t_flag *flags);
int				prt_c(t_flag *flags, va_list args);
int				prt_s(t_flag *flags, va_list args);
int				prt_u(t_flag *flags, va_list args);
int				prt_x(t_flag *flags, va_list args);
int				prt_p(t_flag *flags, va_list args);
int				prt_int(t_flag *flags, va_list args);

#endif
