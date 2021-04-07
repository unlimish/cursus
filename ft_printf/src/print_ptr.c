#include "../inc/ft_printf.h"
#include "../inc/utils.h"
#include <stdint.h>

static char		*proc_flags_ptr(t_flag *flags, char *str_hex, uintptr_t va_int)
{
	int	strap_len;

	strap_len = 2;
	flags->va_len = ft_strlen(str_hex);
	if ((flags->acc == END_OF_DOT || flags->acc == 0) &&
										va_int == (uintptr_t)NULL)
		flags->va_len = 0;
	if (flags->acc - flags->va_len > 0 && flags->acc > 0)
		flags->zero_len = flags->acc - flags->va_len;
	if (flags->field - flags->va_len > 0 && flags->field > 0)
	{
		if (flags->zero_len > 0)
			flags->field_len = flags->field -
					(strap_len + flags->va_len + flags->zero_len);
		else
			flags->field_len = flags->field - (strap_len + flags->va_len);
	}
	if (flags->flg_zero == true && flags->field_len > 0 && flags->acc < 0)
		flags->zero_len = flags->field_len;
	if (flags->flg_zero == true && flags->acc > 0)
		flags->flg_zero = false;
	return (str_hex);
}

static	int		print(t_flag *flags, int result_len, char *strap, char *str_hex)
{
	if (flags->flg_minus == true)
		result_len += write(1, strap, 2);
	if (flags->flg_minus == true && flags->zero_len > 0)
		result_len += print_zero(flags->zero_len);
	if (flags->flg_minus == true)
		result_len += write(1, str_hex, flags->va_len);
	if (flags->flg_zero == false && flags->field_len > 0)
		result_len += print_space(flags->field_len);
	if (flags->zero_len > 0 && flags->flg_minus == false)
		result_len += write(1, strap, 2);
	if (flags->flg_minus == false && flags->zero_len > 0)
		result_len += print_zero(flags->zero_len);
	if (flags->flg_minus == false)
	{
		if (flags->flg_minus == false && flags->zero_len <= 0)
			result_len += write(1, strap, 2);
		result_len += write(1, str_hex, flags->va_len);
	}
	return (result_len);
}

int				prt_p(t_flag *flags, va_list args)
{
	int				result_len;
	uintptr_t		va_int;
	char			*str_hex;
	char			*strap;

	result_len = 0;
	va_int = (uintptr_t)va_arg(args, void *);
	str_hex = va_int > 9 ? ft_dechex(va_int) : ft_itoa(va_int);
	flags->va_len = ft_strlen(str_hex);
	if (flags->conv_spec == 'X')
		ft_toupper(str_hex);
	str_hex = proc_flags_ptr(flags, str_hex, va_int);
	strap = flags->conv_spec == 'X' ? "0X" : "0x";
	result_len = print(flags, result_len, strap, str_hex);
	return (result_len);
}
