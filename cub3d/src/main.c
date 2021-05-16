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
# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17

typedef struct  s_vars {
        void    *mlx;
        void    *win;
		double	pos_x;
		double	pos_y;
		double	dir_x;
		double	dir_y;
		double	plane_x;
		double	plane_y;
		double	move_speed;
		double	rotate_speed;

}               t_vars;

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

void	ver_line(t_vars *vars, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(vars->mlx, vars->win, x, y, color);
		y++;
	}
}

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
				side_dist_x < delta_dist_x;
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

		int color;
		if (world_map[map_x][map_y] == 1)
			color = 0xFF0000;
		else if (world_map[map_x][map_y] == 2)
			color = 0x00FF00;
		else if (world_map[map_x][map_y] == 3)
			color = 0x0000FF;
		else if (world_map[map_x][map_y] == 4)
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;

		if (side == 1)
			color = color / 2;

		ver_line(vars, x, draw_start, draw_end, color);

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
	return (0);
}

static int key_hook(int keycode, t_vars *vars)
{
	printf("%d\n", keycode);
    if (keycode == K_CROSS)
	{
        mlx_destroy_window(vars->mlx, vars->win);
		exit (0);
	}
}

int	key_press(int key, t_vars *vars)
{
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
	if (key == K_CROSS)
	{
        mlx_destroy_window(vars->mlx, vars->win);
		exit (0);
	}
	if (key == K_ESC)
		exit(0);
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

	vars->pos_x = 12;
	vars->pos_y = 5;
	vars->dir_x = -1;
	vars->dir_y = 0;
	vars->plane_x = 0;
	vars->plane_y = 0.66;
	vars->move_speed = 0.05;
	vars->rotate_speed = 0.05;

	vars->win = mlx_new_window(vars->mlx, width, height, "mlx");

	// mlx_loop_hook(vars->mlx, &main_loop, vars);
	// mlx_hook(vars->win, X_EVENT_KEY_PRESS, 0, &key_hook, vars);

	// mlx_loop(vars->mlx);

	// open_map_path(argv[1]);

	mlx_key_hook(vars->win, key_hook, vars);
	mlx_loop_hook(vars->mlx, &main_loop, vars);
	mlx_hook(vars->win, K_ESC, 1L<<17, close_window, vars);

	mlx_loop(vars->mlx);
}
