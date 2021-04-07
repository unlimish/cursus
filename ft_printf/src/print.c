#include "../inc/ft_printf.h"
#include "../inc/print.h"

int		print_format(t_flag *flags, va_list args)
{
	int	print_len;

	print_len = 0;
	if (flags->conv_spec == '%')
		print_len += prt_percent(flags);
	else if (flags->conv_spec == 'c')
		print_len += prt_c(flags, args);
	else if (flags->conv_spec == 's')
		print_len += prt_s(flags, args);
	else if (flags->conv_spec == 'p')
		print_len += prt_p(flags, args);
	else if (flags->conv_spec == 'd' || flags->conv_spec == 'i')
		print_len += prt_int(flags, args);
	else if (flags->conv_spec == 'u')
		print_len += prt_u(flags, args);
	else if (flags->conv_spec == 'x' || flags->conv_spec == 'X')
		print_len += prt_x(flags, args);
	return (print_len);
}
