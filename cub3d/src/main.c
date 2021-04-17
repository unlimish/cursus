#include <X11/Xlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#include <stdio.h>
#include <stdlib.h>
#include "../minilibx-linux/mlx.h"
#include "../inc/main.h"

typedef struct  s_vars {
        void    *mlx;
        void    *win;
}               t_vars;

int             close(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
	exit (0);
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

int     main(void)
{
	void    *img;
	void    *mlx;
	int	x;
	int y;
	t_vars	*vars;

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 300, 300, "Hi, I'm Unlimish");
	img = mlx_new_image(vars->mlx, 1920, 1080);


	x = 0;
	while (x < 300)
	{
		y = 0;
		while (y < 150)
		{
			mlx_pixel_put(vars->mlx, vars->win, x, y, 0xcf3177);
			y++;
		}
		x++;
	}

	x = 0;
		while (x < 300)
	{
		y = 150;
		while (y < 300)
		{
			mlx_pixel_put(vars->mlx, vars->win, x, y, 0x25ced1);
			y++;
		}
		x++;
	}

	x = 150;
		while (x < 300)
	{
		y = 150;
		while (y < 300)
		{
			mlx_pixel_put(vars->mlx, vars->win, x, y, 0x6fbaa2);
			y++;
		}
		x++;
	}

	mlx_key_hook(vars->win, key_hook, vars);
	mlx_hook(vars->win, K_ESC, 1L<<17, close, vars);

	mlx_loop(vars->mlx);
}
