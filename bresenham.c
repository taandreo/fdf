#include "fdf.h"

static void	pixel(t_fdf *fdf, int x, int y, int color)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, x, y, color);
}

void bresenham(t_fdf *fdf, int x0, int y0, int x1, int y1)
{
   int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
   int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1; 
   int err = dx+dy, e2; /* error value e_xy */
 
   for(;;){  /* loop */
	  pixel(fdf, x0, y0, WHITE);
      if (x0==x1 && y0==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
   }
}

// void bresenham3d(int x0, int y0, int z0, int x1, int y1, int z1)
// {
//    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
//    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
//    int dz = abs(z1-z0), sz = z0<z1 ? 1 : -1; 
//    int dm = max(dx,dy,dz), i = dm; /* maximum difference */
//    x1 = y1 = z1 = dm/2; /* error offset */
 
//    for(;;) {  /* loop */
//       setPixel(x0,y0,z0);
//       if (i-- == 0) break;
//       x1 -= dx; if (x1 < 0) { x1 += dm; x0 += sx; } 
//       y1 -= dy; if (y1 < 0) { y1 += dm; y0 += sy; } 
//       z1 -= dz; if (z1 < 0) { z1 += dm; z0 += sz; } 
//    }
// }

void	centrallize(t_fdf *fdf)
{
	fdf->x0 = (WIDTH -  fdf->x * LINESIZE) / 2;
	fdf->y0 = (HEIGHT - fdf->y * LINESIZE) / 2;
}

// void	zoom()

void	make3d(t_point *po, double angle, double z)
{
	float	x;
	float	y;

	x = (po->x - po->y) * cos(angle);
	y = (po->x + po->y) * sin(angle) - (po->z * z);
	po->x = (int) x;
	po->y = (int) y;
}

void	edu_equation(t_point *po)
{
	float x;
	float y;
	float a;
	float b;

	a = 0.61;
	b = 0.78;
	x = po->x * cos(b) + po->y - po->z * sin(b);
	y = po->x * sin(b) * sin(a) + po->y * cos(a);

	po->x = x;
	po->y = y;
}

/*
// a => 35.264° 0.61
// b => 45° 0.78
// Xi e Yi Zi são valores iniciais
  Xf = Xi*cos(b) + Yi - Zi*sin(b);
  Yf = Xi*sin(b)*sin(a) + Yi*cos(a);
*/