#include <stdio.h>
int main()
{
	printf("#	%d\n", ft_isascii('#'));
	printf("7	%d\n", ft_isascii('7'));
	printf("a	%d\n", ft_isascii('a'));
	printf("Z	%d\n", ft_isascii('Z'));
	printf("\\a	%d\n", ft_isascii((int)'\a'));
	printf("\\r	%d\n", ft_isascii((int)'\r'));
	printf("ｱ	%d\n", ft_isascii((int)"ｱ"));
}
