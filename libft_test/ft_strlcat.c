#include <stdio.h>
#include <string.h>

int main(void)
{
	char dest[100] = "I'm";
	char src[100] = "Unlimish";

	printf("return:%d dest : %s \t src %s \t\n", ft_strlcat(dest, src, 2), dest, src);
}
