#include <stdio.h>
#include <limits.h>
int main()
{
	printf("%s\n", ft_itoa(-2147));
	printf("%s\n", ft_itoa(-2147000000000));
	printf("%s\n", ft_itoa(-0));
	printf("%s\n", ft_itoa(INT_MIN));
	printf("%s\n", ft_itoa(INT_MAX));
}
