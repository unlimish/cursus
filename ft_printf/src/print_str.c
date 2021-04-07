#include "../inc/ft_printf.h"
#include "../inc/print.h"
#include "../inc/utils.h"

int				prt_c(t_flag *flags, va_list args)
{
	int		print_len;
	char	va_char;

	print_len = 0;
	va_char = (char)va_arg(args, int);
	if (flags->field >= 2)
	{
		if (flags->flg_minus == true)
			print_len += write(1, &va_char, 1);
		if (flags->field > 0)
			print_len += print_space(flags->field - 1);
		if (flags->flg_minus == false)
			print_len += write(1, &va_char, 1);
	}
	else
		print_len += write(1, &va_char, 1);
	return (print_len);
}

static	void	proc_flags(t_flag *flags, char *va_str)
{
	if (flags->acc == END_OF_DOT || flags->acc == 0)
		flags->va_len = 0;
	else
		flags->va_len = ft_strlen(va_str);
	if (flags->flg_minus == true && flags->flg_zero == true)
		flags->flg_zero = false;
	if (flags->acc < flags->va_len && flags->acc > 0 &&
										flags->acc_nega_aster != true)
		flags->va_len = flags->acc;
	if (flags->field > flags->va_len)
		flags->field_len = flags->field - flags->va_len;
}

int				prt_s(t_flag *flags, va_list args)
{
	int		print_len;
	char	*va_str;

	print_len = 0;
	va_str = (char *)va_arg(args, char *);
	if (flags->acc == END_OF_DOT && flags->field == INIT)
		return (print_len);
	if (!va_str)
		va_str = "(null)";
	proc_flags(flags, va_str);
	if (flags->field_len > 0)
	{
		if (flags->flg_minus == true)
			print_len += write(1, va_str, flags->va_len);
		if (flags->flg_zero == true)
			print_len += print_zero(flags->field_len);
		else if (flags->field_len > 0)
			print_len += print_space(flags->field_len);
		if (flags->flg_minus == false)
			print_len += write(1, va_str, flags->va_len);
	}
	else
		print_len += write(1, va_str, flags->va_len);
	return (print_len);
}
