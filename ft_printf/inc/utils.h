#ifndef UTILS_H
# define UTILS_H

# include "ft_printf.h"
# include "print.h"

char			*ft_itoa(long n);
char			*ft_utoa(unsigned int n);
char			*ft_strcpy(char *dest, char *src);
char			*ft_dechex(unsigned long dec);
char			*ft_toupper(char *c);
char			*ft_strjoin(char const *s1, char const *s2);
void			*ft_memcpy(void *dest, const void *src, size_t n);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
size_t			u_count_len(unsigned int n);
size_t			count_len(int n);
int				print_zero(int len);
int				print_space(int len);
#endif
