/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:45:41 by tairribe          #+#    #+#             */
/*   Updated: 2022/12/10 21:17:18 by tairribe         ###   ########.fr       */
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
	return(0);
}

void	init_point(t_point *po, int x, int y, int z)
{
	po->x = x;
	po->y = y;
	po->z = z;
}


void	zoom(t_point *src, t_point *dst, int x0, int y0)
{
	src->x *= LINESIZE;
	src->x += x0;
	src->y *= LINESIZE;
	src->y += y0;
	dst->x *= LINESIZE;
	dst->x += x0;
	dst->y *= LINESIZE;
	dst->y += y0;
}


void	draw(t_fdf *fdf)
{
	t_point dst;
	t_point src;
	int 	i;
	int		j;
	
	init_point(&src, 0, 0, 0);
	init_point(&dst, 0, 0, 0);
	i = 0;
	while(i < fdf->y - 1)
	{
		j = 0;
		while (j < fdf->x)
		{	
			// LINE
			// SRC
			src.x = j;
			src.y = i;
			src.z = fdf->coord[i][j];
			// DST
			dst.x = j + 1;
			dst.y = i;
			dst.z = fdf->coord[i][j + 1];
			zoom(&src, &dst, fdf->x0, fdf->y0);
			make3d(&src, &dst, fdf->angle, 20);
			// edu_equation_02(&src, &dst);
			bresenham(fdf, &src, &dst);
			// COLUNM
			// SRC
			src.x = j;
			src.y = i;
			src.z = fdf->coord[i][j];
			// DST
			dst.x = j;
			dst.y = i + 1;
			dst.z = fdf->coord[i + 1][j];
			zoom(&src, &dst, fdf->x0, fdf->y0);
			make3d(&src, &dst, fdf->angle, 20);
			// edu_equation_02(&src, &dst);
			// edu_equation(&column);
			bresenham(fdf, &src, &dst);
			j++;
		}
		src.y += LINESIZE;
		src.x = 0;
		i++;
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
	centrallize(&fdf);
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
