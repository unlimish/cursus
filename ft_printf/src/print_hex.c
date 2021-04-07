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

static void		proc_flags(t_flag *flags, unsigned int va_int)
{
	if ((flags->acc == END_OF_DOT || flags->acc == 0) && va_int == 0)
		flags->va_len = 0;
	if (flags->acc == 0 && flags->flg_zero == true)
		flags->flg_zero = false;
	if (flags->acc - flags->va_len > 0 && flags->acc > 0)
		flags->zero_len = flags->acc - flags->va_len;
	proc_field_len(flags);
	if (flags->flg_zero == true && flags->field_len > 0 && flags->zero_len < 0
			&& (flags->acc_nega_aster == true || flags->acc < 0))
	{
		flags->zero_len = flags->field_len;
		flags->field_len = INIT;
	}
	if (flags->flg_zero == true && flags->acc > 0)
		flags->flg_zero = false;
}

int				prt_x(t_flag *flags, va_list args)
{
	int				result_len;
	unsigned int	va_int;
	char			*str_hex;

	result_len = 0;
	va_int = va_arg(args, unsigned int);
	str_hex = va_int > 9 ? ft_dechex(va_int) : ft_itoa(va_int);
	flags->va_len = ft_strlen(str_hex);
	if (flags->conv_spec == 'X')
		ft_toupper(str_hex);
	proc_flags(flags, va_int);
	if (flags->flg_minus == true && flags->zero_len != INIT)
		result_len += print_zero(flags->zero_len);
	if (flags->flg_minus == true)
		result_len += write(1, str_hex, flags->va_len);
	if (flags->flg_zero == false && flags->field_len != INIT)
		result_len += print_space(flags->field_len);
	if (flags->flg_minus == false && flags->zero_len != INIT)
		result_len += print_zero(flags->zero_len);
	if (flags->flg_minus == false)
		result_len += write(1, str_hex, flags->va_len);
	free(str_hex);
	return (result_len);
}
