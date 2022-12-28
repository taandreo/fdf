/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:23:36 by tairribe          #+#    #+#             */
/*   Updated: 2022/12/28 02:22:48 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static char	**get_mt(char *s)
{
	char	*l;
	char	**mt;

	l = ft_strtrim(s, "\n\r ");
	mt = ft_split(l, ' ');
	free(s);
	free(l);
	return (mt);
}

static void	get_xy(t_fdf *fdf, char *filename)
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
		if (fdf->y)
			free(line);
		fdf->y++;
		line = get_next_line(fd);
	}
	close(fd);
}

static t_crd	get_crd(char *s)
{
	char	*color;
	t_crd	c;
	char	*z;

	color = ft_strchr(s, ',');
	if (color)
	{
		z = ft_substr(s, 0, color - s);
		c.z = ft_atoi(z);
		color++;
		c.color = ft_atoi_base(color, 16);
		free(z);
	}
	else
	{
		c.z = ft_atoi(s);
		c.color = WHITE;
	}
	return (c);
}

static t_crd	*get_line(char *raw_line, int size, t_fdf *fdf)
{
	char	**mt;
	t_crd	*p;
	int		i;

	i = 0;
	p = ft_calloc(size, sizeof(t_crd));
	mt = get_mt(raw_line);
	if (get_mt_size((void **) mt) != size)
		fdf->err = 1;
	while (mt[i])
	{
		p[i] = get_crd(mt[i]);
		i++;
	}
	free_mt((void **) mt);
	return (p);
}

void	get_coordinates(t_fdf *fdf, char *filename)
{
	int		fd;
	char	*raw_line;
	int		i;

	get_xy(fdf, filename);
	fd = open_file(filename);
	fdf->coord = ft_calloc(fdf->y, sizeof(t_crd *) + 1);
	fdf->coord[fdf->y] = NULL;
	i = 0;
	while (i < fdf->y)
	{
		raw_line = get_next_line(fd);
		fdf->coord[i++] = get_line(raw_line, fdf->x, fdf);
	}
	close(fd);
	if (fdf->err)
		exit_fdf(fdf, "find wrong line number.");
}
