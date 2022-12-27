/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:45:41 by tairribe          #+#    #+#             */
/*   Updated: 2022/12/27 20:39:48 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_fdf(t_fdf *fdf)
{
	fdf->x = 0;
	fdf->y = 0;
	fdf->x0 = 0;
	fdf->y0 = 0;
	fdf->mlx_ptr = NULL;
	fdf->win_ptr = NULL;
	fdf->coord = NULL;
	fdf->angle = 0.5;
	fdf->z = 1;
	fdf->up = 0;
}

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
	return (0);
}

static void	calc_linesize(t_fdf *fdf)
{
	fdf->line_size = ft_min(fdf->win_width / fdf->x / 2,
			fdf->win_height / fdf->y / 2);
	if (fdf->line_size < LINESIZE_MIN)
		fdf->line_size = LINESIZE_MIN;
}

static int	start_fdf(t_fdf *fdf, char *filename)
{
	fdf->img = NULL;
	fdf->win_height = HEIGHT;
	fdf->win_width = WIDTH;
	calc_linesize(fdf);
	fdf->mlx_ptr = mlx_init();
	if (fdf->mlx_ptr == NULL)
	{
		exit_fdf(fdf);
		print_error("Starting mlx.");
	}
	fdf->win_ptr = mlx_new_window(
			fdf->mlx_ptr, fdf->win_width, fdf->win_height, filename);
	if (fdf->win_ptr == NULL)
	{
		exit_fdf(fdf);
		print_error("Starting new window.");
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	char	*filename;
	t_fdf	fdf;

	if (argc != 2)
		usage();
	filename = argv[1];
	init_fdf(&fdf);
	get_coordinates(&fdf, filename);
	start_fdf(&fdf, filename);
	draw(&fdf);
	mlx_key_hook(fdf.win_ptr, key_press, &fdf);
	mlx_hook(fdf.win_ptr, WIN_CLOSE, 0, exit_fdf, &fdf);
	mlx_loop(fdf.mlx_ptr);
}
