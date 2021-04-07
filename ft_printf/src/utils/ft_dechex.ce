#include "../../inc/ft_printf.h"

static size_t	count_hex(unsigned long dec)
{
	size_t	len;

	len = 0;
	while (dec)
	{
		len++;
		dec /= 16;
	}
	return (len);
}

char			*ft_dechex(unsigned long dec)
{
	char	*result;
	size_t	hex_len;

	hex_len = count_hex(dec);
	if (!(result = malloc(sizeof(char) * (hex_len + 1))))
		return (NULL);
	result[hex_len] = '\0';
	hex_len--;
	while (dec)
	{
		result[hex_len--] = "0123456789abcdef"[dec % 16];
		dec /= 16;
	}
	return (result);
}
