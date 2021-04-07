#include <stdio.h>
int main()
{
	char **tmp;
	int i = 0;
	tmp = ft_split("ABC,DE,F,GHIJ,,,K,L", ',');
	while (i != 6)
	{
		printf("%s\n", tmp[i]);
		i++;
	}
}
