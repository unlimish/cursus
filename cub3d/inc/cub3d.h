#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "../libft/libft.h"

# define K_ESC 33
# define K_CROSS 65307

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
