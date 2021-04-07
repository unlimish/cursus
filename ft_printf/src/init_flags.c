#include "../inc/ft_printf.h"
#include "../inc/proc_fmt.h"

void			init_flags(t_flag *flags)
{
	flags->flg_minus = false;
	flags->flg_zero = false;
	flags->is_nega = false;
	flags->acc_nega_aster = false;
	flags->field = INIT;
	flags->acc = INIT;
	flags->conv_spec = INIT;
	flags->zero_len = INIT;
	flags->field_len = INIT;
	flags->va_len = INIT;
}
