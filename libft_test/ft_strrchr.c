#include <stdio.h>
#include <string.h>
int main()
{
	char search = 'A';
	char tmp[32] = "ABCDAFG";
	printf("FT: 	%p\n", ft_strrchr(tmp, search));
	printf("ORIG:	%p\n", strrchr(tmp, search));
	printf("FT:	%s\n", ft_strrchr(tmp, search));
	printf("ORIG:	%s\n", strrchr(tmp, search));
}
