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
# define WIDTH 1200
# define HEIGHT 900
# define LINESIZE_MIN 1
# define Z_ANGLE 0.785
# define X_ANGLE 0.955

# define KEY_ESC 53

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			color;
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
	int c0;
	int c1;
	int d;
} 				t_bresenham;

typedef struct s_crd
{
	int	color;
	int z;
}		t_crd;

typedef struct s_img
{
	void		*ptr;
	char		*data;
	int			pixels;
	int			size_line;
	int			endian;
} t_img;

typedef struct	s_fdf
{
	int			x;
	int			y;
	int			x0;
	int			y0;
	int			win_width;
	int			win_height;
	int			line_size;
	t_crd		**coord;
	void		*mlx_ptr;
	void		*win_ptr;
	double		angle;
	t_img		*img;
}				t_fdf;



void	get_coordinates(t_fdf *fdf, char *filename);

void	print_error(char *s);
void	usage();
void	bresenham(t_fdf *fdf, t_point *src, t_point *dst);
void	make3d(t_point *po, double angle, double z);
void	edu_equation_05(t_point *po);
int		free_mt(void **mt);

int		ft_abs(int value);
void	pixel(t_fdf *fdf, int x, int y, int color);
void	zoom(t_fdf *fdf, t_point *po);
void	start_point(t_fdf *fdf);
// CENTRALIZE
void	centralize2(t_fdf *fdf, t_point *src, t_point *dst);
void	centralize(t_fdf *fdf, t_point *po);
void	centralize_before(t_fdf *fdf, t_point *po);
void	centralize_after(t_fdf *fdf, t_point *po);
// 3D
void    rotate_z(t_point *po, float angle);
void    rotate_x(t_point *po, float angle, int zm);

#endif
