#include "../../inc/utils.h"

size_t			count_len(int n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		i++;
	}
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(long n)
{
	size_t	len;
	char	*result;

	len = count_len(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	if (n == -2147483648)
		return (ft_strcpy(result, "-2147483648"));
	if (n == 2147483648)
		return (ft_strcpy(result, "2147483648"));
	if (n < 0)
	{
		result[0] = '-';
		n = n * -1;
	}
	result[len] = '\0';
	if (n == 0)
		result[0] = '0';
	while (n != 0)
	{
		result[--len] = n % 10 + '0';
		n /= 10;
	}
	return (result);
}
