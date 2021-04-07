#include "../libft/libft.h"

int main(void)
{
	printf("ft_memset\n");
	char memset_array[32] = "ABCDEFG";
	ft_memset(memset_array + 3, '*', 3);
	printf("%s\n", memset_array);

	printf("\n");

	// printf("ft_bzero\n");
	// char bzero_array[32] = "ABCDEFG";
	// ft_bzero(bzero_array, 3);
	// printf("%c", *bzero_array);


	printf("ft_memcpy\n");
	char	s1[7] = "ABCDEF";
	char	s2[7] = "000000";
	printf("s1:%s <- s2:%s (3bytes)\n", s1, s2);
	ft_memcpy(s1,s2, 3);
	printf("%s", s1);

	printf("\n");

	printf("ft_memcpy\n");
	char s1[32] = "000000";
	char s2[32] = "ABCDEF";
	printf("%s\n", ft_memccpy(s1, s2,'C' ,sizeof(s1)));
	s1[32] = "000000";
	s2[32] = "ABCDEF";
	printf("%s\n", ft_memccpy(s1, s2,'Z' ,sizeof(s1)));
	printf("%s", s1);

	printf("\n");

	printf("ft_memmove")
	char tmp[32] = "ABCDEFG";
	char tmp2[32] = "ABCDEFG";
	printf("%p\n", ft_memmove(tmp, tmp + 3, 3));
	memmove(tmp2, tmp2 + 3, 3);
	printf("%s\n",tmp);
	printf("%s\n",tmp2);
}
