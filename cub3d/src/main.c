#include <X11/Xlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../minilibx-linux/mlx.h"
#include "../inc/cub3d.h"
#include "../inc/key_macros.h"

# define width 640
# define height 480
# define tex_height 64
# define tex_width 64
# define X_EVENT_KEY_PRESS	2
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
		void    *mlx;
		void    *win;
		t_img	img;
		double	pos_x;
		double	pos_y;
		double	dir_x;
		double	dir_y;
		double	plane_x;
		double	plane_y;
		double	move_speed;
		double	rotate_speed;
		int		**buf;
		int		texture[8][tex_height * tex_width];

}				t_vars;

int	world_map[24][24] = {
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
						};

void	draw(t_vars *info)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			info->img.data[y * width + x] = info->buf[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}
// void	ver_line(t_vars *vars, int x, int y1, int y2, int color)
// {
// 	int	y;
// 	y = y1;
// 	while (y <= y2)
// 	{
// 			mlx_pixel_put(vars->mlx, vars->win, x, y, color);
// 		y++;
// 	}
// }

void	calc(t_vars *vars)
{
	int	x;

	x = 0;
	while (x < width)
	{
		double	camera_x = 2 * x / (double)width - 1;
		double	ray_dir_x = vars->dir_x + vars->plane_x * camera_x;
		double	ray_dir_y = vars->dir_y + vars->plane_y * camera_x;

		int map_x = (int)vars->pos_x;
		int	map_y = (int)vars->pos_y;

		double	side_dist_x;
		double	side_dist_y;

		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);
		double perp_wall_dist;

		int step_x;
		int	step_y;

		int	hit = 0;
		int	side = 0;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (vars->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - vars->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (vars->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - vars->pos_y) * delta_dist_y;
		}

		while (hit == 0)
		{
			if (side_dist_x <side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (world_map[map_x][map_y] > 0)
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map_x - vars->pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - vars->pos_y + (1 - step_y) / 2) / ray_dir_y;

		int line_height = (int)(height / perp_wall_dist);

		int draw_start = -line_height / 2 + height / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + height / 2;
		if (draw_end >= height)
			draw_end = height - 1;

		int	tex_num = world_map[map_x][map_y];

		double wall_x;
		if (side == 0)
			wall_x = vars->pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = vars->pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);

		int tex_x = (int)(wall_x * (double) tex_width);
		if (side == 0 && ray_dir_x > 0)
			tex_x = tex_width - tex_x - 1;
		if (side == 1 && ray_dir_y < 0)
			tex_x = tex_width - tex_x - 1;

		double step = 1.0 * tex_height / line_height;
		double tex_pos = (draw_start - height / 2 + line_height / 2) * step;
		for (int y = draw_start; y < draw_end; y++)
		{
			int tex_y = (int)tex_pos & (tex_height - 1);
			tex_pos += step;
			int color = vars->texture[tex_num][tex_height * tex_y + tex_x];
			if (side == 1)
				color = (color >> 1) & 8355711;
			vars->buf[y][x] = color;
		}

		for (int y = 0; y < draw_start; y++)
		{
			int tex_y = (int)tex_pos & (tex_height - 1);
			tex_pos += step;
			int color = vars->texture[0][tex_height * tex_y + tex_x];
			if (side == 1)
				color = (color >> 1) & 8355711;
			vars->buf[y][x] = color;
		}
		for (int y = draw_end; y < height; y++)
		{
			int tex_y = (int)tex_pos & (tex_height - 1);
			tex_pos += step;
			int color = vars->texture[0][tex_height * tex_y + tex_x];
			if (side == 1)
				color = (color >> 1) & 8355711;
			vars->buf[y][x] = color;
		}

		// ver_line(vars, x, 0, draw_start, 0xe8ebe488);
		// ver_line(vars, x, draw_start, draw_end, color);
		// ver_line(vars, x, draw_end, height, 0x25ce0ee);

		x++;
	}
}

static int	close_window(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
	exit (0);
}

int	main_loop(t_vars *vars)
{
	calc(vars);
	draw(vars);
	return (0);
}

int	key_press(int key, t_vars *vars)
{
	printf("%d\n", key);
	fflush(stdout);
	if (key == K_W)
	{
		if (!world_map[(int)(vars->pos_x + vars->dir_x * vars->move_speed)][(int)(vars->pos_y)])
			vars->pos_x += vars->dir_x * vars->move_speed;
		if (!world_map[(int)(vars->pos_x)][(int)(vars->pos_y + vars->dir_y * vars->move_speed)])
			vars->pos_y += vars->dir_y * vars->move_speed;
	}
	//move backwards if no wall behind you
	if (key == K_S)
	{
		if (!world_map[(int)(vars->pos_x - vars->dir_x * vars->move_speed)][(int)(vars->pos_y)])
			vars->pos_x -= vars->dir_x * vars->move_speed;
		if (!world_map[(int)(vars->pos_x)][(int)(vars->pos_y - vars->dir_y * vars->move_speed)])
			vars->pos_y -= vars->dir_y * vars->move_speed;
	}
	//rotate to the right
	if (key == K_D)
	{
		//both camera direction and camera plane must be rotated
		double olddir_x = vars->dir_x;
		vars->dir_x = vars->dir_x * cos(-vars->rotate_speed) - vars->dir_y * sin(-vars->rotate_speed);
		vars->dir_y = olddir_x * sin(-vars->rotate_speed) + vars->dir_y * cos(-vars->rotate_speed);
		double oldplane_x = vars->plane_x;
		vars->plane_x = vars->plane_x * cos(-vars->rotate_speed) - vars->plane_y * sin(-vars->rotate_speed);
		vars->plane_y = oldplane_x * sin(-vars->rotate_speed) + vars->plane_y * cos(-vars->rotate_speed);
	}
	//rotate to the left
	if (key == K_A)
	{
		//both camera direction and camera plane must be rotated
		double olddir_x = vars->dir_x;
		vars->dir_x = vars->dir_x * cos(vars->rotate_speed) - vars->dir_y * sin(vars->rotate_speed);
		vars->dir_y = olddir_x * sin(vars->rotate_speed) + vars->dir_y * cos(vars->rotate_speed);
		double oldplane_x = vars->plane_x;
		vars->plane_x = vars->plane_x * cos(vars->rotate_speed) - vars->plane_y * sin(vars->rotate_speed);
		vars->plane_y = oldplane_x * sin(vars->rotate_speed) + vars->plane_y * cos(vars->rotate_speed);
	}
	if (key == K_ESC)
		close_window(vars);
	return (0);
}

int     main(int argc, char **argv)
{
	void    *img;
	int	x;
	int y;
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	vars->mlx = mlx_init();

	vars->pos_x = 5;
	vars->pos_y = 5;
	vars->dir_x = -1;
	vars->dir_y = 0;
	vars->plane_x = 0;
	vars->plane_y = 0.66;

vars->buf = (int **)malloc(sizeof(int *) * height);
	for (int i = 0; i < height; i++)
	{
		vars->buf[i] = (int *)malloc(sizeof(int) * width);
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			vars->buf[i][j] = 0;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < tex_height * tex_width; j++)
		{
			vars->texture[i][j] = 0;
		}
	}

	for (int x = 0; x < tex_width; x++)
	{
		for (int y = 0; y < tex_height; y++)
		{
			int xorcolor = (x * 256 / tex_width) ^ (y * 256 / tex_height);
			int ycolor = y * 256 / tex_height;
			int xycolor = y * 128 / tex_height + x * 128 / tex_width;
			vars->texture[0][tex_width * y + x] = 65536 * 254 * (x != y && x != tex_width - y); //flat red texture with black cross
			vars->texture[1][tex_width * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			vars->texture[2][tex_width * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			vars->texture[3][tex_width * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			vars->texture[4][tex_width * y + x] = 256 * xorcolor; //xor green
			vars->texture[5][tex_width * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			vars->texture[6][tex_width * y + x] = 65536 * ycolor; //red gradient
			vars->texture[7][tex_width * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}

	vars->move_speed = 0.05;
	vars->rotate_speed = 0.05;

	vars->win = mlx_new_window(vars->mlx, width, height, "");

	vars->img.img = mlx_new_image(vars->mlx, width, height);
	vars->img.data = (int *)mlx_get_data_addr(vars->img.img, &vars->img.bpp, &vars->img.size_l, &vars->img.endian);

	mlx_loop_hook(vars->mlx, &main_loop, vars);
	mlx_hook(vars->win, X_EVENT_KEY_PRESS, 1L<<0, &key_press, vars);
	mlx_hook(vars->win, X_EVENT_KEY_EXIT, 1L << 17, close_window, vars);

	mlx_loop(vars->mlx);
}
