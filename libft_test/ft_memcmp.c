#include <stdio.h>
int	main()
{
	char s1[32] = "AAAAAA";
	char s2[32] = "AAABAA";
	printf("%d\n",ft_memcmp(s1,s2, sizeof(s2)));
	printf("%d\n",memcmp(s1,s2, sizeof(s2)));
}
