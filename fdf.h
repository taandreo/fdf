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

# define WHITE 0xFFFFFF
# define WIDTH 1280
# define HEIGHT 720
# define LINESIZE 30

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
} 				t_point;

typedef struct	s_bresenham
{
	int	dx;
	int dy;
	int ix;
	int iy;
	int	x0;
	int y0;
	int x1;
	int y1;
	int d;
} 				t_bresenham;

typedef struct s_crd
{
	int	color;
	int z;
}		t_crd;

typedef struct	s_fdf
{
	int			x;
	int			y;
	int			x0;
	int			y0;
	int			**coord;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	double		angle;
}				t_fdf;

void	get_coordinates(t_fdf *fdf, char *filename);
void	centralize(t_fdf *fdf);
void	print_error(char *s);
void	usage();
void	bresenham(t_fdf *fdf, int x0, int y0, int x1, int y1);
void	make3d(t_point *po, double angle, double z);
void	edu_equation_05(t_point *po);

int		free_mt(void **mt);

int		ft_abs(int value);
void	pixel(t_fdf *fdf, int x, int y, int color);
void	zoom(t_point *po);
void	start_point(t_fdf *fdf);

// void    edu_equation_03(t_point *p);
// void	edu_equation_02(t_point *src, t_point *dst);
// void	edu_equation(t_point *src, t_point *dst);
// void    edu_equation_04(t_point *p);
void	centralize2(t_fdf *fdf, t_point *src, t_point *dst);
void	centralize_before(t_fdf *fdf, t_point *po);
void	centralize_after(t_point *po);

#endif
