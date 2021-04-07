#include <stdio.h>
int main()
{
	printf("9	%d\n", ft_isalnum((int)'9'));
	printf("F	%d\n", ft_isalnum((int)'F'));
	printf("y	%d\n", ft_isalnum((int)'y'));
	printf("5	%d\n", ft_isalnum('5'));
	printf("C	%d\n", ft_isalnum('C'));
	printf("\\0	%d\n", ft_isalnum((int)'\0'));
}
