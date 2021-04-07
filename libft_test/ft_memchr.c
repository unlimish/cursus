#include <stdio.h>
int main()
{
	char tmp[32] = "ABCDEF";
	printf("input:		%s\n", tmp);
	printf("result(Z):	%s\n", ft_memchr(tmp, 'Z', sizeof(tmp)));
	printf("result(D):	%s\n", ft_memchr(tmp, 'D', sizeof(tmp)));
}
