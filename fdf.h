#ifndef FDF_H
# define FDF_H

#include <stdio.h>
#include <unistd.h>
#include "libft/include/libft.h"
#include "libft/include/ft_printf.h"
#include <strings.h>
#include <stdlib.h>
#include <mlx.h>
#include <fcntl.h>
#include <math.h>

# define WHITE	0xFFFFFF
# define WIDTH  1280
# define HEIGHT 720
# define LINESIZE 20

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
} 				t_point;

typedef struct	s_fdf
{
	int			x;
	int			y;
	int			x0;
	int			y0;
	int			**coord;
	t_point		**points;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	double		angle;
}				t_fdf;

void	centrallize(t_fdf *fdf);
void	print_error(char *s);
void	usage();
void	bresenham(t_fdf *fdf, int x0, int y0, int x1, int y1);
void	make3d(t_point *po, double angle, double z);
void	edu_equation(t_point *po);

#endif
