#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include "get_next_line_utils.c"

int main(int argc,char **argv)
{
	int fd;
	char *line;
	int	return_code;
	int i = 0;

	return_code = 0;

	fd = open("./test", O_RDONLY);
	while (return_code >= 0)
	{
		return_code = get_next_line(fd, &line);
		printf("return:%d %s\n",return_code, line[0]);
		if (return_code == 0)
			return (0);
		i++;
	}


	return 0;
}
