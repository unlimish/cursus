#include "../inc/ft_printf.h"
#include "../inc/print.h"
#include "../inc/utils.h"

int	prt_percent(t_flag *flags)
{
	int	print_len;

	print_len = 0;
	if (flags->field >= 2)
	{
		if (flags->flg_minus == true)
			print_len += write(1, "%%", 1);
		if (flags->flg_zero == true && flags->flg_minus == false)
			print_len += print_zero(flags->field - 1);
		else
			print_len += print_space(flags->field - 1);
		if (flags->flg_minus == false)
			print_len += write(1, "%%", 1);
	}
	else
		print_len += write(1, "%%", 1);
	return (print_len);
}
