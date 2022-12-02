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

# define WHITE	0xFFFFFF

typedef struct	s_fdf
{
	int			x;
	int			y;
	int			**coord;
	void		*mlx_ptr;
	void		*win_ptr;
}				t_fdf;

typedef struct	s_point
{
	int			x;
	int			y;
} 				t_point;

void	print_error(char *s);
void	usage();

#endif
