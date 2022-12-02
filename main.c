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
	fdf->mlx_ptr = NULL;
	fdf->win_ptr = NULL;
	fdf->coord = NULL;
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
	print_coordinates(fdf);
	close(fd);
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
	// fdf.mlx_ptr = mlx_init(); 
	// fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 1000, 1000, filename);

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
