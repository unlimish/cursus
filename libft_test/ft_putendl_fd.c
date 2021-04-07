#include <fcntl.h>
int main()
{
	ft_putendl_fd("ABC", open("./file", O_WRONLY));
}
