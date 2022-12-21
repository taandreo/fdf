#include "fdf.h"

void	init_fdf(t_fdf *fdf)
{
	fdf->x = 0;
	fdf->y = 0;
	fdf->x0 = 0;
	fdf->y0 = 0;
	fdf->mlx_ptr = NULL;
	fdf->win_ptr = NULL;
	fdf->coord = NULL;
	fdf->angle = 0.5;
}

int	get_mt_size(void **mt)
{
	int	i;

	i = 0;
	while(mt[i])
		i++;
	return (i);
}

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

t_crd	get_crd(char *s)
{
	char	*color;
	t_crd	c;
	char	*z;

	// c = ft_calloc(1, sizeof(t_crd));
	color = ft_strchr(s, ',');
	if (color)
	{
		z = ft_substr(s, 0, color - s);
		c.z = ft_atoi(z);
		color++;
		c.color = ft_atoi_base(color, 16);
		free(z);
	} 
	else {
		c.z     = ft_atoi(s);
		c.color = WHITE;
	}
	return (c);
}

t_crd	*get_line(char *raw_line, int size)
{
	char	**mt;
	t_crd 	*p;
	int 	i;

	i = 0;
	p = ft_calloc(size, sizeof(t_crd));
	mt = get_mt(raw_line);
	if (get_mt_size((void**) mt) != size)
	{
		free_mt((void **) mt);
		print_error("Found wrong line length.");
	}
	while (mt[i])
	{
		p[i] = get_crd(mt[i]);
		// p[i] = ft_atoi(mt[i]);
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
			ft_printf("[%i] ", fdf->coord[j][i++].z);
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
