#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "ft_mini_ls.h"
#include <stdio.h>

static	int		count_dir(char *path)
{
	DIR		*dir;
	size_t	amount;
	struct dirent *stream;

	amount = 0;
	dir = opendir(path);
	if (dir == NULL)
	{
		return (0);
	}
	while ((stream = readdir(dir)) != NULL)
	{
		if (stream->d_name[0] != '.')
		{
			amount++;
		}
	}
	return (amount);
}

void			swap(struct s_file *x, struct s_file *y)
{
	struct	s_file	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

void			bubble_sort(struct s_file array[], int array_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < array_size - 1)
	{
		j = array_size - 1;
		while (j >= i + 1)
		{
			if (array[j].time < array[j - 1].time)
				swap(&array[j], &array[j - 1]);
			j--;
		}
		i++;
	}
}

int				main(int argc, char **argv)
{
	DIR				*dir;
	size_t			i;
	size_t			amount_path;
	struct dirent	*dir_stream;
	struct s_file	*dir_modded;
	struct stat		stat_buf;
	char			*path;

	i = 0;
	path = "./";
	if (argc > 1)
	{
		path = argv[1];
	}
	dir = opendir(path);
	if (dir == NULL)
	{
		ft_putendl_fd(strerror(2), 2);
		return (2);
	}
	amount_path = count_dir(path);
	dir_modded = ft_calloc(amount_path + 1, sizeof(t_file));
	while ((dir_stream = readdir(dir)) != NULL)
	{
		if (dir_stream->d_name[0] != '.')
		{
			dir_modded[i].name = ft_strdup(dir_stream->d_name);
			char *temp = ft_strjoin(path, dir_modded[i].name);
			lstat(temp, &stat_buf);
			dir_modded[i].time = stat_buf.st_mtime;
			i++;
		}
	}
	dir_modded[i].name = NULL;
	bubble_sort(dir_modded, amount_path);
	i = 0;
	while (i <= amount_path && dir_modded[i].name != NULL)
	{
		if (dir_modded[i].name != NULL)
		{
			ft_putendl_fd(dir_modded[i].name, 1);
		}
		i++;
	}
	closedir(dir);
	return (0);
}
