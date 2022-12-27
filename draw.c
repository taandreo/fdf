/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:24:00 by tairribe          #+#    #+#             */
/*   Updated: 2022/12/27 02:02:04 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	start_img(t_fdf *fdf)
{
	if (fdf->img == NULL)
		fdf->img = ft_calloc(1, sizeof(t_img));
	else
		mlx_destroy_image(fdf->mlx_ptr, fdf->img->ptr);
	fdf->img->ptr = mlx_new_image(
			fdf->mlx_ptr, fdf->win_width, fdf->win_height);
	if (fdf->img->ptr == NULL)
	{
		print_error("Starting new image.");
		exit_fdf(fdf);
	}
	fdf->img->data = mlx_get_data_addr(fdf->img->ptr, &fdf->img->pixels,
			&fdf->img->size_line, &fdf->img->endian);
}

t_point	init_point(int x, int y, int z, int color)
{
	t_point	po;

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
	rotate_x(src, X_ANGLE, fdf->line_size * fdf->z);
	centralize_after(fdf, src);
	zoom(fdf, dst);
	centralize_before(fdf, dst);
	rotate_z(dst, Z_ANGLE);
	rotate_x(dst, X_ANGLE, fdf->line_size * fdf->z);
	centralize_after(fdf, dst);
	bresenham(fdf, src, dst);
}

void	draw_line(t_fdf *fdf, int y)
{
	int		x;
	t_point	dst;
	t_point	src;

	x = 0;
	while (x < fdf->x)
	{	
		if (x != fdf->x -1)
		{
			src = init_point(x, y, fdf->coord[y][x].z, fdf->coord[y][x].color);
			dst = init_point(x + 1, y, fdf->coord[y][x + 1].z,
					fdf->coord[y][x + 1].color);
			new_line(fdf, &src, &dst);
		}
		if (y != fdf->y - 1)
		{
			src = init_point(x, y, fdf->coord[y][x].z, fdf->coord[y][x].color);
			dst = init_point(x, y + 1, fdf->coord[y + 1][x].z,
					fdf->coord[y + 1][x].color);
			new_line(fdf, &src, &dst);
		}
		x++;
	}
}

void	draw(t_fdf *fdf)
{
	int		y;

	y = 0;
	start_img(fdf);
	while (y < fdf->y)
	{
		draw_line(fdf, y);
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->ptr, 0, 0);
}
