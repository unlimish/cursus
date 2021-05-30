#ifndef CUB3D_H
# define CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"

# define WIDTH 640
# define HEIGHT 480
# define tex_height 64
# define tex_width 64
# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT	17

typedef	struct s_img	{
		void	*img;
		int		*data;

		int		size_l;
		int		bpp;
		int		endian;
		int		img_width;
		int		img_height;
}				t_img;

typedef struct  s_vars {
		void	*mlx;
		void	*win;
		t_img	img;
		double	pos_x;
		double	pos_y;
		double	dir_x;
		double	dir_y;
		double	plane_x;
		double	plane_y;
		double	move_speed;
		double	rotate_speed;
		int		buf[HEIGHT][WIDTH];
		double	z_buf[WIDTH];
		int		**texture;
}				t_vars;


typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_tex
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_tex;

typedef struct s_map
{
	t_tex	texture;
}	t_map;

#endif
