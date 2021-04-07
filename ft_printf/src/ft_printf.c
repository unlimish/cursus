#include "../inc/ft_printf.h"
#include "../inc/print.h"
#include "../inc/proc_fmt.h"
#include "../inc/utils.h"
#include <stdio.h>

static	void	proc_format(t_flag *flags, va_list args, const char **fmt)
{
	init_flags(flags);
	judge_flags(flags, fmt);
	input_width(flags, args, fmt);
	input_acc(flags, args, fmt);
	input_conv_spec(flags, fmt);
}

static	void	free_flags(t_flag *flags)
{
	free(flags);
	flags = NULL;
}

int				ft_printf(const char *fmt, ...)
{
	t_flag		*flags;
	va_list		args;
	int			result_len;
	const char	*start;

	result_len = 0;
	if (fmt == NULL)
		return (-1);
	va_start(args, fmt);
	while (*fmt)
	{
		start = fmt;
		if (*fmt != '%')
			result_len += ft_putstr_len(&start, &fmt);
		else
		{
			if (!(flags = malloc(sizeof(t_flag))))
				return (-1);
			proc_format(flags, args, &fmt);
			result_len += print_format(flags, args);
			free_flags(flags);
		}
	}
	va_end(args);
	return (result_len);
}
