#include <limits.h>
#include <string.h>
#include <stdio.h>
#include "get_next_line.h"

static int	divide_each_line(char **line, char **save, char *buf)
{
	char	*inputted_line;
	char	*tmp;
	char	*eol_ptr;

	eol_ptr = ft_strchr(buf, '\n');
	inputted_line = *line;
	tmp = ft_substr(buf, 0, eol_ptr - buf);
	if (tmp == NULL)
		return (ERROR);
	*line = ft_strjoin(*line, tmp);
	free(inputted_line);
	free(tmp);
	if (!(*line))
		return (ERROR);
	*save = ft_substr(eol_ptr + 1, 0, ft_strlen(eol_ptr + 1));
	if (save == NULL)
		return (ERROR);
	return (SUCCESS);
}

static int	join_line_buf(char **line, char *buf)
{
	char	*tmp;
	size_t	len;
	size_t	i;

	len = ft_strlen(buf);
	tmp = *line;
	*line = ft_strjoin(tmp, buf);
	free(tmp);
	i = 0;
	while (len > i)
		buf[i++] = '\0';
	if (!(*line))
		return (ERROR);
	return (READ_CONTINUE);
}

static int	join_line_char_buf(char **line, char **char_buf)
{
	char	*tmp;
	char	*eol_ptr;

	eol_ptr = ft_strchr(*char_buf, '\n');
	if (eol_ptr != NULL)
	{
		tmp = *line;
		*line = ft_substr(*char_buf, 0, eol_ptr - *char_buf);
		free(tmp);
		if (!(*line))
			return (ERROR);
		tmp = *char_buf;
		*char_buf = ft_substr(eol_ptr + 1, 0, ft_strlen(eol_ptr + 1));
		free(tmp);
		if (!(char_buf))
			return (ERROR);
		return (SUCCESS);
	}
	else
	{
		tmp = *line;
		*line = *char_buf;
		*char_buf = NULL;
		free(tmp);
		return (READ_CONTINUE);
	}
}

static int	read_fd(int fd, char **line, char **char_buf)
{
	ssize_t		read_size;
	int			status_code;
	char		*buf_for_read;

	status_code = READ_CONTINUE;
	buf_for_read = malloc(BUFFER_SIZE + 1);
	if (buf_for_read == NULL)
		return (ERROR);
	if (read_size = read(fd, buf_for_read, BUFFER_SIZE))
	{
		while (status_code == READ_CONTINUE)
		{
			buf_for_read[read_size] = '\0' ;
			if (ft_strchr(buf_for_read, '\n'))
				status_code = divide_each_line(line, char_buf, buf_for_read);
			else
				status_code = join_line_buf(line, buf_for_read);
		}
	}
	free(buf_for_read);
	if (status_code == READ_CONTINUE && read_size == 0)
		status_code = END_OF_FILE;
	else if (status_code == READ_CONTINUE && read_size == -1)
		status_code = ERROR;
	return (status_code);
}

int		get_next_line(int fd, char **line)
{
	int			flag;
	static char	*char_buf;
	int			fd_err_range;

	fd_err_range = fd < 0 || FOPEN_MAX <= fd;
	flag = READ_CONTINUE;
	if (fd_err_range || line == NULL || BUFFER_SIZE <= 0)
		return (ERROR);
	if (!(*line = (char *)malloc(1)))
		return (ERROR);
	*line[0] = '\0';
	if (char_buf)
		flag = join_line_char_buf(line, &char_buf);
	if (flag == READ_CONTINUE)
		flag = read_fd(fd, line, &char_buf);
	return (flag);
}
