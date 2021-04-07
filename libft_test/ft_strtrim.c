#include <stdio.h>
int main()
{
	char set[3] = " F";
	char *s1 = "    ABC DEF   ";
	printf("%s\n", ft_strtrim(s1, set));
}
