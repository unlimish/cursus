#include "../../inc/utils.h"

int		print_space(int len)
{
	int	i;

	i = 0;
	if (len <= 0)
		return (i);
	while (i < len)
	{
		write(1, " ", 1);
		i++;
	}
	return (i);
}

int		print_zero(int len)
{
	int	i;

	i = 0;
	if (len <= 0)
		return (i);
	while (i < len)
	{
		write(1, "0", 1);
		i++;
	}
	return (i);
}
