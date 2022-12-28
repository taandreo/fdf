/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:45:29 by tairribe          #+#    #+#             */
/*   Updated: 2022/12/28 03:55:02 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include <stdlib.h>
# include <mlx.h>
# include <fcntl.h>
# include <math.h>

# define WHITE 0xFFFFFF
# define WIDTH 1200
# define HEIGHT 900

// # define WIDTH 2560
// # define HEIGHT 1440

# define LINESIZE_MIN 1
# define Z_ANGLE 0.785
# define X_ANGLE 0.955

# define KEY_ESC 0xff1b
# define WIN_CLOSE 17

typedef struct s_point
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_point;

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	ix;
	int	iy;
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	c0;
	int	c1;
	int	d;
}			t_bresenham;

typedef struct s_crd
{
	int	color;
	int	z;
}		t_crd;

typedef struct s_img
{
	void		*ptr;
	char		*data;
	int			pixels;
	int			size_line;
	int			endian;
}				t_img;

typedef struct s_fdf
{
	int			x;
	int			y;
	float		z;
	int			x0;
	int			y0;
	int			win_width;
	int			win_height;
	int			line_size;
	t_crd		**coord;
	void		*mlx_ptr;
	void		*win_ptr;
	double		angle;
	int			up;
	int			err;
	t_img		*img;
}				t_fdf;

// PARSE
void	get_coordinates(t_fdf *fdf, char *filename);
// BRESENHAM
void	bresenham(t_fdf *fdf, t_point *src, t_point *dst);
// MAIN
int		exit_fdf(t_fdf *fdf, char *err);
// DRAW
void	draw(t_fdf *fdf);
// PIXEL
void	pixel(t_fdf *fdf, int x, int y, int color);
// CALC
void	zoom(t_fdf *fdf, t_point *po);
void	centralize_before(t_fdf *fdf, t_point *po);
void	centralize_after(t_fdf *fdf, t_point *po);
void	rotate_z(t_point *po, float angle);
void	rotate_x(t_point *po, float angle, float zm);
// UTILS
int		ft_min(int a, int b);
int		get_mt_size(void **mt);
int		free_mt(void **mt);
int		open_file(char *filename);
void	print_error(char *s);
void	usage(void);
int		ft_abs(int value);
// HOOKS
int		exit_fdf_win(t_fdf *fdf);
int		key_press(int keycode, void *param);
#endif