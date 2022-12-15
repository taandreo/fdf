#include "fdf.h"

void	pixel(t_fdf *fdf, int x, int y, int color)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, x, y, color);
}

void	centralize(t_fdf *fdf)
{
	fdf->x0 = (WIDTH  - fdf->x * LINESIZE) / 2;
	fdf->y0 = (HEIGHT - fdf->y * LINESIZE) / 2;
}

void	start_point(t_fdf *fdf)
{
	fdf->x0 = (WIDTH / 2) - ((fdf->x / 2) * LINESIZE);
	fdf->y0 = (HEIGHT / 2) - ((fdf->y / 2) * LINESIZE);
	printf("x0: %i y0: %i\n", fdf->x0, fdf->y0);
}

void	centralize2(t_fdf *fdf, t_point *src, t_point *dst)
{
	src->x = src->x + fdf->x0;
	src->y = src->y + fdf->y0;

	dst->x = dst->x + fdf->x0;
	dst->y = dst->y + fdf->y0;
}

void	centralize_before(t_fdf *fdf, t_point *src, t_point *dst)
{
	src->x -= (fdf->x * LINESIZE) / 2;
	src->y -= (fdf->y * LINESIZE) / 2;

	dst->x -= (fdf->x * LINESIZE) / 2;
	dst->y -= (fdf->y * LINESIZE) / 2;
}

void	centralize_after(t_point *src, t_point *dst)
{
	src->x += WIDTH  / 2;
	src->y += HEIGHT / 2;

	dst->x += WIDTH  / 2;
	dst->y += HEIGHT / 2;
}

void	zoom(t_point *src, t_point *dst)
{
	src->x *= LINESIZE;
	// src->x += x0;
	src->y *= LINESIZE;
	// src->y += y0;
	dst->x *= LINESIZE;
	// dst->x += x0;
	dst->y *= LINESIZE;
	// dst->y += y0;
}

void	make3d(t_point *src, t_point *dst, double angle, double z)
{
	float	x;
	float	y;

	x = (src->x - src->y) * cos(angle);
	y = (src->x + src->y) * sin(angle) - (src->z * z);
	src->x = (int) x;
	src->y = (int) y;
	x = (dst->x - dst->y) * cos(angle);
	y = (dst->x + dst->y) * sin(angle) - (dst->z * z);
	dst->x = (int) x;
	dst->y = (int) y;
}

void	edu_equation(t_point *src, t_point *dst)
{
	float x;
	float y;
	float a;
	float b;

	a = 0.61;
	b = 0.78;
	x = src->x * cos(b) + src->y - src->z * sin(b);
	y = src->x * sin(b) * sin(a) + src->y * cos(a);

	src->x = (int) x;
	src->y = (int) y;

	a = 0.61;
	b = 0.78;
	x = dst->x * cos(b) + dst->y - dst->z * sin(b);
	y = dst->x * sin(b) * sin(a) + dst->y * cos(a);

	dst->x = (int) x;
	dst->y = (int) y;

}

void	edu_equation_02(t_point *src, t_point *dst)
{
	float	x;
	float	y;

	x = (src->x - src->z) / sqrt(2); 
  	y = (src->x + 2 * src->y + src->z) / sqrt(6);
	src->x = (int) x;
	src->y = (int) y;

	x = (dst->x - dst->z) / sqrt(2); 
  	y = (dst->x + 2 * dst->y + dst->z) / sqrt(6);
	dst->x = (int) x;
	dst->y = (int) y;
}

void    edu_equation_03(t_point *p)
{
	int x;
	int y;
	float A;
	float B;

	A = 0.615;
	B = 0.785;

    x = (p->z * sin(A)) + (p->x * cos(A));
    y = (p->z * cos(A) * sin(B)) - (p->x * sin(A) * sin(B)) + (p->y * cos(B));

	p->x = x;
	p->y = y;
	p->z = 0;
}

void    edu_equation_04(t_point *p)
{
	int x;
	int y;
	float A;
	float B;

	B = 0.615;
	A = 0.785;

	x = p->z * cos(B) - p->x * sin(B);
	y = p->z * sin(A) * sin(B) + p->y * cos(A) + p->x * sin(A) * cos(B);

	p->x = x;
	p->y = y;
	p->z = 0;
}

/*

*/

/*
// a => 35.264° 0.61
// b => 45° 0.78
// p->xi e p->yi Zi são valores iniciais
  Xf = Xi*cos(b) + Yi - Zi*sin(b);
  Yf = Xi*sin(b)*sin(a) + Yi*cos(a);
*/

/*
pseudo código

dx = x1 - x0;
dy = y1 - y0;

e = 2dy
dne = 2dy - 2dx

decision variable = d = 2dy - dx


*/