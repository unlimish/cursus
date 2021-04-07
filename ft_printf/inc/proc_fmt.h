#ifndef PROC_FMT_H
# define PROC_FMT_H

void			init_flags(t_flag *flags);
void			judge_flags(t_flag *flags, const char **fmt);
void			input_width(t_flag *flags, va_list args, const char **fmt);
void			input_acc(t_flag *flags, va_list args, const char **fmt);
void			input_conv_spec(t_flag *flags, const char **fmt);
#endif
