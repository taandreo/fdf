#include "fdf.h"

void	pixel(t_fdf *fdf, int x, int y, int color)
{
	char *pixel;

	if (x < 0 || x > fdf->win_width || y < 0 || y > fdf->win_height)
		return ;
	pixel = fdf->img->data + (fdf->img->size_line * y) + \
		((fdf->img->pixels / 8) * x);
	*(unsigned int *)pixel = color;
}

void	start_point(t_fdf *fdf)
{
	fdf->x0 = (fdf->win_width / 2) + ((fdf->x / 2) * fdf->line_size);
	fdf->y0 = (fdf->win_height / 2) + ((fdf->y / 2) * fdf->line_size);
	printf("x0: %i y0: %i\n", fdf->x0, fdf->y0);
}


void	centralize_before(t_fdf *fdf, t_point *po)
{
	po->x -= (fdf->x * fdf->line_size) / 2;
	po->y -= (fdf->y * fdf->line_size) / 2;
}

void	centralize_after(t_fdf *fdf, t_point *po)
{
	po->x += fdf->win_width  / 2;
	po->y += (fdf->win_height + (fdf->y * fdf->line_size) / 2) / 2;
}

void	zoom(t_fdf *fdf, t_point *po)
{
	po->x *= fdf->line_size;
	po->y *= fdf->line_size;
}

void	make3d(t_point *po, double angle, double z)
{
	float	x;
	float	y;

	x = (po->x - po->y) * cos(angle);
	y = (po->x + po->y) * sin(angle) - (po->z * z);
	po->x = (int) x;
	po->y = (int) y;
}

void    rotate_z(t_point *po, float angle)
{
    float    x;
    float    y;

    x = po->x;
    y = po->y;
    po->x = x * cos(angle) - y * sin(angle);
    po->y = x * sin(angle) + y * cos(angle);
    
}

void    rotate_x(t_point *po, float angle, int zm)
{
    float    y;
    float    z;

    y = po->y;
    z = po->z;
    po->y = y * cos(angle) - (z * sin(angle) * zm);
    po->z = y * sin(angle) + (z * cos(angle) * zm);
}