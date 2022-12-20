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

// void	centralize2(t_fdf *fdf, t_point *src, t_point *dst)
// {
// 	src->x = src->x + fdf->x0;
// 	src->y = src->y + fdf->y0;

// 	dst->x = dst->x + fdf->x0;
// 	dst->y = dst->y + fdf->y0;
// }

void	centralize(t_fdf *fdf, t_point *po)
{
	po->x -= (fdf->x * fdf->line_size) / 2;
	po->y -= (fdf->y * fdf->line_size) / 2;

	po->x += fdf->win_width  / 2;
	po->y += (fdf->win_height + (fdf->y * fdf->line_size) / 2) / 2;
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

// void	edu_equation_05(t_point *po)
// {
// 	float B = 0.785;
// 	float C = 0.955;
// 	int x;
// 	int y;
	
// 	x = (po->x * cos(B)) - (po->z * sin(B));
//     y = (po->x * cos(C) * cos(B)) + (po->y * cos(C) * cos(B)) - (po->z * sin(C));
// 	po->x = x;
// 	po->y = y;
// }
// void	edu_equation(t_point *src, t_point *dst)
// {
// 	float x;
// 	float y;
// 	float a;
// 	float b;

// 	a = 0.61;
// 	b = 0.78;
// 	x = src->x * cos(b) + src->y - src->z * sin(b);
// 	y = src->x * sin(b) * sin(a) + src->y * cos(a);

// 	src->x = (int) x;
// 	src->y = (int) y;

// 	a = 0.61;
// 	b = 0.78;
// 	x = dst->x * cos(b) + dst->y - dst->z * sin(b);
// 	y = dst->x * sin(b) * sin(a) + dst->y * cos(a);

// 	dst->x = (int) x;
// 	dst->y = (int) y;

// }

// void	edu_equation_02(t_point *src, t_point *dst)
// {
// 	float	x;
// 	float	y;

// 	x = (src->x - src->z) / sqrt(2); 
//   	y = (src->x + 2 * src->y + src->z) / sqrt(6);
// 	src->x = (int) x;
// 	src->y = (int) y;

// 	x = (dst->x - dst->z) / sqrt(2); 
//   	y = (dst->x + 2 * dst->y + dst->z) / sqrt(6);
// 	dst->x = (int) x;
// 	dst->y = (int) y;
// }

// void    edu_equation_03(t_point *p)
// {
// 	int x;
// 	int y;
// 	float A;
// 	float B;

// 	A = 0.615;
// 	B = 0.785;

//     x = (p->z * sin(A)) + (p->x * cos(A));
//     y = (p->z * cos(A) * sin(B)) - (p->x * sin(A) * sin(B)) + (p->y * cos(B));

// 	p->x = x;
// 	p->y = y;
// 	p->z = 0;
// }

// void    edu_equation_04(t_point *p)
// {
// 	int x;
// 	int y;
// 	float A;
// 	float B;

// 	B = 0.615;
// 	A = 0.785;

// 	x = p->z * cos(B) - p->x * sin(B);
// 	y = p->z * sin(A) * sin(B) + p->y * cos(A) + p->x * sin(A) * cos(B);

// 	p->x = x;
// 	p->y = y;
// 	p->z = 0;
// }

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