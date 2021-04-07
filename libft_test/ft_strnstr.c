#include <stdio.h>
int main()
{
	char	*s1 = "Foo Bar";
	char	*s2 = "Bar";
	printf("LIBFT:	%s\n", ft_strnstr(s1, s2, sizeof(s1)));
	printf("ORIG:	%s\n", strnstr(s1, s2, sizeof(s1)));
}
