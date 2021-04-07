#include <stdio.h>
int main()
{
	printf("orig:	%p\n", calloc(12, 2));
	printf("libft:	%p\n", ft_calloc(12, 2));
}
