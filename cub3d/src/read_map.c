#include "../inc/cub3d.h"

int	open_map_path(char *path)
{
	int	fd;
	int	gnl_status_code;
	char	*str_line;

	fd = 0;
	fd = open(path, O_RDONLY);
	gnl_status_code = 1;
	while(gnl_status_code == 1)
	get_next_line(fd, );
	return (fd);
}

void	read_map()
{

}
