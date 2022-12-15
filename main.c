/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:45:41 by tairribe          #+#    #+#             */
/*   Updated: 2022/12/14 22:49:19 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_line_simple(t_fdf fdf, int x, int y, int size)
{
	int i;
	
	i = 0;
	while (i < size){
		mlx_pixel_put(fdf.mlx_ptr, fdf.win_ptr, x, y, WHITE);
		x++;
		i++;
	}
}

void	free_fdf(t_fdf *fdf)
{
	free_mt((void **) fdf->coord);
}

int	start_fdf(t_fdf *fdf, char *filename)
{
	if ((fdf->mlx_ptr = mlx_init()) == NULL)
	{
		free_fdf(fdf);
		print_error("Starting mlx.");
	}
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, filename);
	// fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	start_point(fdf);
	return(0);
}

t_point	init_point(int x, int y, int z)
{
	t_point po;
	
	po.x = x;
	po.y = y;
	po.z = z;

	return (po);
}

void	new_line(t_fdf *fdf, t_point *src, t_point *dst)
{
	zoom(src);
	centralize_before(fdf, src);
	make3d(src, fdf->angle, 20);
	centralize_after(src);

	zoom(dst);
	centralize_before(fdf, dst);
	make3d(dst, fdf->angle, 20);
	centralize_after(dst);

	bresenham(fdf, src->x, src->y, dst->x, dst->y);
}

void	draw(t_fdf *fdf)
{
	t_point dst;
	t_point src;
	int 	x;
	int		y;
	
	y = 0;
	while(y < fdf->y)
	{
		x = 0;
		while (x < fdf->x)
		{	
			if (x != fdf->x -1)
			{
				src = init_point(x, y, fdf->coord[y][x]);
				dst = init_point(x + 1, y, fdf->coord[y][x + 1]);
				new_line(fdf, &src, &dst);
			}
			if (y != fdf->y - 1){
				src = init_point(x, y, fdf->coord[y][x]);
				dst = init_point(x, y + 1, fdf->coord[y + 1][x]);
				new_line(fdf, &src, &dst);
			}
			x++;
		}
		y++;
	}
}

int	main(int argc, char *argv[])
{
	char	*filename;
	t_fdf	fdf;

	if (argc != 2)
		usage();
	
	filename = argv[1];
	get_coordinates(&fdf, filename);
	// centralize(&fdf);
	start_fdf(&fdf, filename);
	draw(&fdf);
	mlx_loop(fdf.mlx_ptr);
	// if (fdf.mlx_ptr == NULL)
	// 	print_error("setting up the connection to the graphical system");
	
	// if (fdf.win_ptr == NULL)
	// 	print_error("creating a new window");
	
	// put_line_simple(fdf, 100, 100, 100);
	// // mlx_string_put(fdf.mlx_ptr, fdf.win_ptr, 10, 10, WHITE, "42asdfasdfasdfasdfasdfasdfasdfasdfasd");
	// mlx_loop(fdf.mlx_ptr);
	// // printf("%i\n", fd);
	// mlx_destroy_window(fdf.mlx_ptr, fdf.win_ptr);
}
