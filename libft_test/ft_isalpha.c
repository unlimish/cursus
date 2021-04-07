#include <stdio.h>
int main()
{
	printf("9: %d\n", ft_isalpha((int)'9'));
	printf("F: %d\n", ft_isalpha((int)'F'));
	printf("y: %d\n", ft_isalpha((int)'y'));
	printf("\\0: %d\n", ft_isalpha((int)'\0'));
}
