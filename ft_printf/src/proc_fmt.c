#include "../inc/ft_printf.h"
#include "../inc/proc_fmt.h"

void			judge_flags(t_flag *flags, const char **fmt)
{
	if (**fmt == '%')
		(*fmt)++;
	while (**fmt && ((**fmt == '-') || (**fmt == '0')))
	{
		if (**fmt == '-')
			flags->flg_minus = true;
		else if (**fmt == '0')
			flags->flg_zero = true;
		(*fmt)++;
	}
	return ;
}

void			input_width(t_flag *flags, va_list args, const char **fmt)
{
	bool	used;

	used = false;
	while (**fmt && ((**fmt >= '0' && **fmt <= '9') || **fmt == '*')
		&& **fmt != '.')
	{
		if ((**fmt >= '0' && **fmt <= '9') && flags->field == -1)
			flags->field = ft_atoi(*fmt);
		else if (**fmt == '*' && used == false)
		{
			flags->field = va_arg(args, int);
			used = true;
			if (flags->field < 0)
			{
				flags->flg_minus = true;
				flags->field *= -1;
			}
		}
		(*fmt)++;
	}
	return ;
}

void			get_acc(t_flag *flags, va_list args)
{
	flags->acc = va_arg(args, int);
	flags->acc_nega_aster = (flags->acc < 0) ? true : false;
	flags->acc = flags->acc < 0 ? flags->acc * -1 : flags->acc;
}

void			input_acc(t_flag *flags, va_list args, const char **fmt)
{
	bool	used;
	bool	passed_dot;

	passed_dot = false;
	used = false;
	while (**fmt == '.')
	{
		(*fmt)++;
		passed_dot = true;
	}
	if (passed_dot == true && !(**fmt >= '0' && **fmt <= '9'))
		flags->acc = END_OF_DOT;
	while (**fmt && ((**fmt >= '0' && **fmt <= '9')
					|| **fmt == '*') && **fmt != '.')
	{
		if ((**fmt >= '0' && **fmt <= '9') && flags->acc == -1)
			flags->acc = ft_atoi(*fmt);
		else if (**fmt == '*' && used == false)
		{
			used = true;
			get_acc(flags, args);
		}
		(*fmt)++;
	}
}

void			input_conv_spec(t_flag *flags, const char **fmt)
{
	if (flags->conv_spec == -1 && (**fmt == 'c' || **fmt == 's' || **fmt == 'p'
	|| **fmt == 'd' || **fmt == 'i' || **fmt == 'u' || **fmt == 'x' ||
	**fmt == 'X' || **fmt == '%'))
	{
		flags->conv_spec = **fmt;
		(*fmt)++;
	}
}
