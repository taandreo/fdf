/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:45:41 by tairribe          #+#    #+#             */
/*   Updated: 2022/12/20 17:46:30 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_fdf(t_fdf *fdf)
{
	free_mt((void **) fdf->coord);
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
	fdf->win_height = HEIGHT;
	fdf->win_width = WIDTH;
	calc_linesize(fdf);
	ft_printf("line_size: %i\n", fdf->line_size);
	if ((fdf->mlx_ptr = mlx_init()) == NULL)
	{
		free_fdf(fdf);
		print_error("Starting mlx.");
	}
	if ((fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->win_width, fdf->win_height, filename)) == NULL)
	{
		free_fdf(fdf);
		print_error("Starting new window.");
	}
	start_point(fdf);
	return(0);
}

void	start_img(t_fdf *fdf, t_img *img)
{
	if ((img->ptr = mlx_new_image(fdf->mlx_ptr, fdf->win_width, fdf->win_height)) == NULL)
	{
		free_fdf(fdf);
		print_error("Starting new image.");
	}
	img->data = mlx_get_data_addr(img->ptr, &img->pixels, &img->size_line, &img->endian);
	fdf->img = img;
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
	make3d(src, fdf->angle, fdf->line_size);
	centralize_after(fdf, src);

	zoom(fdf, dst);
	centralize_before(fdf, dst);
	make3d(dst, fdf->angle, fdf->line_size);
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

int	main(int argc, char *argv[])
{
	char	*filename;
	t_fdf	fdf;
	t_img   img;

	if (argc != 2)
		usage();
	
	filename = argv[1];
	get_coordinates(&fdf, filename);
	start_fdf(&fdf, filename);
	start_img(&fdf, &img);
	draw(&fdf);
	mlx_loop(fdf.mlx_ptr);
}
