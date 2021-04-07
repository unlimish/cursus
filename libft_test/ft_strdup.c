#include <stdio.h>
int main()
{
	char src[32] = "ABCDEF";
	char *dest;
	dest = ft_strdup(src);
	printf("src:	%p	%s\n", src, src);
	printf("dest:	%p	%s\n", dest, dest);

}
