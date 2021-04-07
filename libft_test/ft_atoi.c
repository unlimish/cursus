#include <stdio.h>
int main()
{
	printf("ss-+3648:		%d	%d\n", ft_atoi("  -+3648"), atoi("  -+3648"));
	printf("3++:			%d	%d\n", ft_atoi("3++"), atoi("3++"));
	printf("sss200:			%d	%d\n", ft_atoi("   200"), atoi("   200"));
	printf("-1:			%d	%d\n", ft_atoi("-1"), atoi("-1"));
	printf("12345678901:		%d	%d\n", ft_atoi("12345678901"), atoi("12345678901"));
	printf("3.14:			%d	%d\n", ft_atoi("3.14"), atoi("3.14"));
	printf("2147483647:		%d	%d\n", ft_atoi("2147483647"), atoi("2147483647"));
	printf("9223372036854775807:		%d	%d\n", ft_atoi("9223372036854775807"), atoi("9223372036854775807"));
	printf("-9223372036854775806:		%d	%d\n", ft_atoi("-9223372036854775806"), atoi("-9223372036854775806"));
}
