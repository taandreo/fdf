#include "fdf.h"

static void	pixel(t_fdf *fdf, int x, int y, int color)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, x, y, color);
}

void	init_bresenham(t_bresenham *bre, t_point *src, t_point *dst)
{
	bre->dx =  abs(dst->x - src->x);
   	bre->dy = -abs(dst->y - src->y);
   	bre->err = bre->dx + bre->dy; /* error value e_xy */
	bre->e2 = 0;
	bre->x = src->x;
	bre->y = src->y;

	if (src->x < dst->x)
		bre->ix = 1;
	else
		bre->ix = -1;
	
	if (src->y < dst->y)
		bre->iy = 1;
	else
		bre->iy = -1;
}

void plotLine(t_fdf *fdf, int x0, int y0, int x1, int y1)
{
   int dx =  abs(x1 - x0), sx = x0<x1 ? 1 : -1;
   int dy = -abs(y1 - y0), sy = y0<y1 ? 1 : -1; 
   int err = dx+dy, e2;
 
   for(;;){
      pixel(fdf, x0, y0, WHITE);
      if (x0==x1 && y0==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; x0 += sx; } 
      if (e2 <= dx) { err += dx; y0 += sy; }
   }
}

void	bresenham(t_fdf *fdf, t_point *src, t_point *dst)
{
// 	t_bresenham bre;

// 	init_bresenham(&bre, src, dst);
   	
// 	while(1){
// 		pixel(fdf, bre.x, bre.y, WHITE);
// 		if (bre.x == dst->x && bre.y == dst->y)
// 			break;
//       	bre.e2 = 2 * bre.err;
// 		if (bre.e2 >= bre.dy)
// 		{ 
// 			bre.err += bre.dy; 
// 			bre.x += bre.ix; 
// 		}
// 		if (bre.e2 <= bre.dx) 
// 		{
// 			bre.err += bre.dx;
// 			bre.y += bre.ix; 
// 		}
// 		ft_printf("ok");
//    }
	plotLine(fdf, src->x, src->y, dst->x, dst->y);
}

void	centrallize(t_fdf *fdf)
{
	fdf->x0 = (WIDTH -  fdf->x * LINESIZE) / 2;
	fdf->y0 = (HEIGHT - fdf->y * LINESIZE) / 2;
}

// void	zoom()

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

void	( t_)
{

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

/*

*/

/*
// a => 35.264° 0.61
// b => 45° 0.78
// Xi e Yi Zi são valores iniciais
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