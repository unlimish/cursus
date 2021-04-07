#include <stdio.h>
#include <string.h>
int main()
{
	char *s1 = "AAAA";
	char *s2 = "AAAB";
	printf("LIBFT:	%d\n", ft_strncmp(s1, s2, sizeof(s1)));
	printf("ORIG:	%d\n", strncmp((char *)s1, (char *)s2, sizeof(s1)));
}
