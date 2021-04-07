#include "../../inc/ft_printf.h"
#include "../../inc/utils.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*ptr_s;
	char		str_c;
	size_t		len_s;

	ptr_s = (const char *)s;
	str_c = (char)c;
	len_s = ft_strlen(s) + 1;
	while (len_s != 0)
	{
		if (*ptr_s == str_c)
			return ((char *)ptr_s);
		ptr_s++;
		len_s--;
	}
	return (NULL);
}

int		ft_putstr_len(const char **start, const char **fmt)
{
	int	len;

	len = 0;
	if (fmt == NULL)
		return (len);
	while (**fmt && **fmt != '%')
		(*fmt)++;
	len = *fmt - *start;
	write(1, *start, len);
	return (len);
}

int		ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
		c == '\v');
}
