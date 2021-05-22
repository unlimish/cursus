#ifndef CUB3D_H
# define CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <math.h>

# include "../libft/libft.h"

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_res
{
	unsigned long	height;
	unsigned long	width;
}	t_res;

typedef struct s_tex
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_tex;

typedef struct s_map
{
	t_res	resolution;
	t_tex	texture;
}	t_map;

#endif
