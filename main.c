/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:45:41 by tairribe          #+#    #+#             */
/*   Updated: 2022/12/23 17:37:38 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	exit_fdf(t_fdf *fdf)
{
	free_mt((void **) fdf->coord);
	if (fdf->img)
	{
		mlx_destroy_image(fdf->mlx_ptr, fdf->img->ptr);
		free(fdf->img);
	}
	if (fdf->win_ptr)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	if (fdf->mlx_ptr)
	{
		mlx_destroy_display(fdf->mlx_ptr);
		free(fdf->mlx_ptr);
	}
	exit(0);
	return(0);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

void	calc_linesize(t_fdf *fdf)
{
	fdf->line_size = ft_min(fdf->win_width / fdf->x / 2, fdf->win_height / fdf->y / 2);
	if (fdf->line_size < LINESIZE_MIN)
		fdf->line_size = LINESIZE_MIN;
}

int	start_fdf(t_fdf *fdf, char *filename)
{
	fdf->img = NULL;
	fdf->win_height = HEIGHT;
	fdf->win_width = WIDTH;
	calc_linesize(fdf);
	fdf->z = fdf->line_size;
	ft_printf("line_size: %i\n", fdf->line_size);
	if ((fdf->mlx_ptr = mlx_init()) == NULL)
	{
		exit_fdf(fdf);
		print_error("Starting mlx.");
	}
	if ((fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->win_width, fdf->win_height, filename)) == NULL)
	{
		exit_fdf(fdf);
		print_error("Starting new window.");
	}
	start_point(fdf);
	return(0);
}

void	start_img(t_fdf *fdf)
{
	if (fdf->img == NULL)
		fdf->img = ft_calloc(1, sizeof(t_img));
	else
		mlx_destroy_image(fdf->mlx_ptr, fdf->img->ptr);
	if ((fdf->img->ptr = mlx_new_image(fdf->mlx_ptr, fdf->win_width, fdf->win_height)) == NULL)
	{
		print_error("Starting new image.");
		exit_fdf(fdf);
	}
	fdf->img->data = mlx_get_data_addr(fdf->img->ptr, &fdf->img->pixels, &fdf->img->size_line, &fdf->img->endian);
}

t_point	init_point(int x, int y, int z, int color)
{
	t_point po;
	
	po.x = x;
	po.y = y;
	po.z = z;
	po.color = color;

	return (po);
}

void	new_line(t_fdf *fdf, t_point *src, t_point *dst)
{
	zoom(fdf, src);
	centralize_before(fdf, src);
	rotate_z(src, Z_ANGLE);
	rotate_x(src, X_ANGLE, fdf->z);
	centralize_after(fdf, src);

	zoom(fdf, dst);
	centralize_before(fdf, dst);
	rotate_z(dst, Z_ANGLE);
	rotate_x(dst, X_ANGLE, fdf->z);
	centralize_after(fdf, dst);
	
	bresenham(fdf, src, dst);
}

void	draw(t_fdf *fdf)
{
	t_point dst;
	t_point src;
	int 	x;
	int		y;
	
	y = 0;
	start_img(fdf);
	while(y < fdf->y)
	{
		x = 0;
		while (x < fdf->x)
		{	
			if (x != fdf->x -1)
			{
				src = init_point(x, y, fdf->coord[y][x].z, fdf->coord[y][x].color);
				dst = init_point(x + 1, y, fdf->coord[y][x + 1].z, fdf->coord[y][x + 1].color);
				new_line(fdf, &src, &dst);
			}
			if (y != fdf->y - 1){
				src = init_point(x, y, fdf->coord[y][x].z, fdf->coord[y][x].color);
				dst = init_point(x, y + 1, fdf->coord[y + 1][x].z, fdf->coord[y + 1][x].color);
				new_line(fdf, &src, &dst);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->ptr, 0, 0);
}

void	zoom_control(t_fdf *fdf, int keycode)
{
	if (fdf->line_size < 1)
		return ;
	if (keycode == 'w')
	{
		fdf->line_size++;
		draw(fdf);
	}
	if (keycode == 's') {
		fdf->line_size--;
		draw(fdf);
	}
}

void	z_control(t_fdf *fdf, int keycode)
{
	if (keycode == 'z')
	{
		fdf->z++;
		draw(fdf);
	}
	if (keycode == 'x') {
		fdf->z--;
		draw(fdf);
	}
}

int	key_press(int keycode, void *param)
{
	t_fdf *fdf;

	fdf = param;
	if (keycode == KEY_ESC)
		exit_fdf((t_fdf *) param);
	if (ft_strrchr("ws", keycode))
		zoom_control(fdf, keycode);
	if (ft_strrchr("zx", keycode))
		z_control(fdf, keycode);
	return (0);
}

int	main(int argc, char *argv[])
{
	char	*filename;
	t_fdf	fdf;
	if (argc != 2)
		usage();
	
	filename = argv[1];
	get_coordinates(&fdf, filename);
	start_fdf(&fdf, filename);
	draw(&fdf);
	mlx_key_hook(fdf.win_ptr, key_press, &fdf);
	mlx_hook(fdf.win_ptr, 17, 0, exit_fdf, &fdf);
	mlx_loop(fdf.mlx_ptr);
}
