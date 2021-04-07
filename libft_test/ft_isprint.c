#include <stdio.h>
#include "libft.h"
int main()
{
	printf("\\n	%d\n", ft_isprint((int)'\n'));
	printf("!	%d\n", ft_isprint((int)'!'));
	printf("!	%d\n", ft_isprint((int)'!'));
	printf("a	%d\n", ft_isprint((int)'a'));
	printf("A	%d\n", ft_isprint((int)'A'));
	printf("1	%d\n", ft_isprint((int)'1'));
	printf("#	%d\n", ft_isprint((int)'#'));
	printf("~	%d\n", ft_isprint((int)'~'));
}
