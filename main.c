/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:45:41 by tairribe          #+#    #+#             */
/*   Updated: 2022/12/07 20:40:33 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	open_file(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		exit (1);
	}
	return (fd);
}

// Write a line in the x
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

int	free_mt(void **mt)
{
	int	i;

	i = 0;
	while(mt[i])
		free(mt[i++]);
	free(mt);
	return i;
}

char	**get_mt(char *s)
{
	char *l;
	char **mt;

	l = ft_strtrim(s, "\n\r ");
	mt = ft_split(l, ' ');
	free(s);
	free(l);
	return(mt);
}

void	get_xy(t_fdf *fdf, char *filename)
{
	char	*line;	
	int		fd;

	fd = open_file(filename);
	line = get_next_line(fd);
	if (!line)
		print_error("Empty file.");
	fdf->x = free_mt((void **) get_mt(line));
	while (line)
	{
		fdf->y++;
		line = get_next_line(fd);
	}
	close(fd);
}

void	init_fdf(t_fdf *fdf)
{
	fdf->x = 0;
	fdf->y = 0;
	fdf->x0 = 0;
	fdf->y0 = 0;
	fdf->mlx_ptr = NULL;
	fdf->win_ptr = NULL;
	fdf->img_ptr = NULL;
	fdf->coord = NULL;
	fdf->angle = 0.8;
}

int	get_mt_size(void **mt)
{
	int	i;

	i = 0;
	while(mt[i])
		i++;
	return (i);
}

int	*get_line(char *raw_line, int size)
{
	char	**mt;
	int 	*p;
	int 	i;

	i = 0;
	p = ft_calloc(size, sizeof(int));
	mt = get_mt(raw_line);
	if (get_mt_size((void**) mt) != size)
	{
		free_mt((void **) mt);
		print_error("Found wrong line length.");
	}
	while (mt[i])
	{
		p[i] = ft_atoi(mt[i]);
		i++;
	}
	free_mt((void **) mt);
	return (p);
}

void	print_coordinates(t_fdf *fdf)
{
	int	i;
	int j;

	j = 0;
	while (fdf->coord[j])
	{
		i = 0;
		while(i < fdf->x)
			ft_printf("[%i] ", fdf->coord[j][i++]);
		ft_printf("\n");
		j++;
	}	
}

void	get_coordinates(t_fdf *fdf, char *filename)
{
	int		fd;
	char	*raw_line;
	int		i;

	init_fdf(fdf);
	get_xy(fdf, filename);
	fd = open_file(filename);
	fdf->coord = ft_calloc(fdf->y, sizeof(int*) + 1);
	fdf->coord[fdf->y] = NULL;
	i = 0;
	while (i < fdf->y)
	{
		raw_line = get_next_line(fd);
		fdf->coord[i++] = get_line(raw_line, fdf->x);
	}
	// print_coordinates(fdf);
	close(fd);
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


zoom(t_point *src, t_point *dst)
{
	src->x *= LINESIZE;
	src->y *= LINESIZE;
	dst->x *= LINESIZE;
	dst->y *= LINESIZE;
}


void	draw(t_fdf *fdf)
{
	t_point line;
	t_point column;
	t_point src;
	int 	i;
	int		j;
	
	init_point(&src,    0, 0, 0);
	init_point(&line,   0, 0, 0);
	init_point(&column, 0, 0, 0);
	i = 0;
	while(i < fdf->y - 1)
	{
		j = 0;
		src.z = fdf->coord[i][j] * LINESIZE;
		src.x = fdf->x0;
		src.y = fdf->y0;
		printf("(x0: %i, y0: %i)\n", fdf->x0, fdf->y0);
		// make3d(&line, fdf->angle, 1);
		// edu_equation(&line);
		while (j < fdf->x)
		{
			zoom(src, line, x0, y0);
			line.x = src.x + (j + 1) * LINESIZE;
			line.y = src.y + i * LINESIZE;
			// line.y = i;
			line.z = fdf->coord[i][j] * LINESIZE;
			// make3d(&line, fdf->angle, 1);
			// edu_equation(&line);
			bresenham(fdf, src.x, src.y, line.x, line.y);
			column.x = src.x + j * LINESIZE;
			column.y = src.y + (i + 1) * LINESIZE;
			column.z = fdf->coord[i + 1][j] * LINESIZE;
			// make3d(&line, fdf->angle, 1);
			// edu_equation(&column);
			bresenham(fdf, src.x, src.y, column.x, column.y);
			src.x = line.x;
			src.y = line.y;
			src.z = line.z;
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
