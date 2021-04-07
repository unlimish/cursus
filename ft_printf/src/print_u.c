#include "../inc/print.h"
#include "../inc/ft_printf.h"
#include "../inc/utils.h"

static int		prt_u_zero(t_flag *flags, char *va_uint_str)
{
	int	result_len;

	result_len = 0;
	if (flags->flg_minus == false && flags->field_len > 0)
		result_len += print_space(flags->field_len);
	if (flags->zero_len > 0)
		result_len += print_zero(flags->zero_len);
	write(1, va_uint_str, flags->va_len);
	free(va_uint_str);
	if (flags->flg_minus == true)
		result_len += print_space(flags->field_len);
	return (result_len);
}

static void		proc_flags_u(t_flag *flags, unsigned int va_uint)
{
	if ((flags->acc == END_OF_DOT || flags->acc == 0) && va_uint == 0)
		flags->va_len = 0;
	if (flags->acc == 0 && flags->flg_zero == true)
		flags->flg_zero = false;
	if (flags->acc - flags->va_len > 0 && flags->acc > 0)
		flags->zero_len = flags->acc - flags->va_len;
	if (flags->field - flags->va_len > 0 && flags->field > 0)
	{
		if (flags->zero_len > 0)
			flags->field_len = flags->field - (flags->va_len + flags->zero_len);
		else
			flags->field_len = flags->field - flags->va_len;
	}
	if (flags->flg_zero == true && flags->field_len > 0 && flags->zero_len < 0
			&& (flags->acc_nega_aster == true || flags->acc < 0))
	{
		flags->zero_len = flags->field_len;
		flags->field_len = INIT;
	}
	if (flags->flg_zero == true && flags->acc > 0)
		flags->flg_zero = false;
}

static int		has_field(t_flag *flags, int len_space, char *va_uint_str)
{
	if (flags->flg_minus == false && flags->field_len > 0)
	{
		if (flags->flg_zero == false)
			len_space += print_space(flags->field_len);
	}
	if (flags->zero_len > 0)
		len_space += print_zero(flags->zero_len);
	write(1, va_uint_str, flags->va_len);
	free(va_uint_str);
	if (flags->flg_minus == true && flags->field_len != -1)
		len_space += print_space(flags->field_len);
	return (len_space);
}

int				prt_u(t_flag *flags, va_list args)
{
	unsigned int	va_uint;
	char			*va_uint_str;
	int				len_space;

	va_uint = 0;
	len_space = 0;
	va_uint = va_arg(args, unsigned int);
	flags->va_len = u_count_len(va_uint);
	va_uint_str = ft_utoa(va_uint);
	proc_flags_u(flags, va_uint);
	if (flags->va_len < flags->field)
		len_space = has_field(flags, len_space, va_uint_str);
	else if (flags->va_len < flags->acc)
		len_space += prt_u_zero(flags, va_uint_str);
	else
	{
		write(1, va_uint_str, flags->va_len);
		free(va_uint_str);
	}
	return (flags->va_len + len_space);
}
