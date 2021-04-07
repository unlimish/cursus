#include "../inc/ft_printf.h"
#include "../inc/utils.h"

static void		proc_field_len(t_flag *flags)
{
	if (flags->field - flags->va_len > 0 && flags->field > 0)
	{
		if (flags->zero_len > 0)
		{
			if (flags->is_nega == true)
				flags->field_len = flags->field -
						(1 + flags->va_len + flags->zero_len);
			else if (flags->is_nega == false)
				flags->field_len = flags->field -
						(flags->va_len + flags->zero_len);
		}
		else if (flags->is_nega == true)
			flags->field_len = flags->field - (flags->va_len + 1);
		else if (flags->is_nega == false)
			flags->field_len = flags->field - flags->va_len;
	}
}

static void		proc_flags(t_flag *flags, char *str_int,
		int va_int)
{
	flags->va_len = ft_strlen(str_int);
	if ((flags->acc == END_OF_DOT || flags->acc == 0) && va_int == 0)
		flags->va_len = 0;
	if ((flags->acc == 0 && flags->flg_zero == true) ||
			(flags->flg_zero == true && flags->flg_minus == true))
		flags->flg_zero = false;
	if (flags->acc - flags->va_len > 0 && flags->acc > 0 &&
						flags->acc_nega_aster == false)
		flags->zero_len = flags->acc - flags->va_len;
	proc_field_len(flags);
	if (flags->flg_zero == true && flags->field_len > 0 && flags->zero_len < 0
			&& (flags->acc_nega_aster == true || flags->acc < 0))
	{
		flags->zero_len = flags->field_len;
		flags->field_len = INIT;
	}
}

static	long	proc_is_nega(t_flag *flags, long va_int)
{
	if (va_int < 0)
	{
		va_int = va_int * -1;
		flags->is_nega = true;
	}
	return (va_int);
}

static	int		prt_int_flg_minus_false(t_flag *flags, int result_len,
															char *str_int)
{
	if (flags->flg_minus == false)
	{
		if (flags->is_nega == true && flags->flg_minus == false &&
			flags->zero_len <= 0)
			result_len += write(1, "-", 1);
		result_len += write(1, str_int, flags->va_len);
	}
	return (result_len);
}

int				prt_int(t_flag *flags, va_list args)
{
	int				result_len;
	long			va_int;
	char			*str_int;

	result_len = 0;
	va_int = (long)va_arg(args, int);
	va_int = proc_is_nega(flags, va_int);
	str_int = ft_itoa(va_int);
	proc_flags(flags, str_int, va_int);
	if (flags->flg_minus == true && flags->is_nega == true)
		result_len += write(1, "-", 1);
	if (flags->flg_minus == true && flags->zero_len != INIT)
		result_len += print_zero(flags->zero_len);
	if (flags->flg_minus == true)
		result_len += write(1, str_int, flags->va_len);
	if (flags->field_len > 0)
		result_len += print_space(flags->field_len);
	if (flags->is_nega == true && flags->zero_len > 0 &&
		flags->flg_minus == false)
		result_len += write(1, "-", 1);
	if (flags->flg_minus == false && flags->zero_len > 0)
		result_len += print_zero(flags->zero_len);
	result_len = prt_int_flg_minus_false(flags, result_len, str_int);
	free(str_int);
	return (result_len);
}
