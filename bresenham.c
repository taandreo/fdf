#include "fdf.h"

void	bresenham_dx(t_fdf *fdf, t_bresenham *bre);
void	bresenham_dy(t_fdf *fdf, t_bresenham *bre);

void	bresenham(t_fdf *fdf, int x0, int y0, int x1, int y1)
{
	t_bresenham bre;
	
	bre.x0 = x0;
	bre.x1 = x1;
	bre.y0 = y0;
	bre.y1 = y1;

	bre.dx = abs(bre.x1 - bre.x0);
	bre.dy = abs(bre.y1 - bre.y0);
	
	if (bre.x1 - bre.x0 < 0)
		bre.ix = -1;
	else
		bre.ix = 1;
	
	if (bre.y1 - bre.y0 < 0)
		bre.iy = -1;
	else
		bre.iy = 1;
	
	if (bre.dx > bre.dy)
		bresenham_dx(fdf, &bre);
	else
		bresenham_dy(fdf, &bre);
}

void	bresenham_dx(t_fdf *fdf, t_bresenham *bre)
{

	bre->d = 2 * bre->dy - bre->dx;
	while (1)
	{
		pixel(fdf, bre->x0, bre->y0, WHITE);
		if (bre->x0 == bre->x1)
			break;
		if (bre->d < 0)
			bre->d = bre->d + 2 * bre->dy;
		else 
		{
			bre->y0 += bre->iy;
			bre->d = bre->d + (2 * bre->dy - 2 * bre->dx);
		}
		bre->x0 += bre->ix;
	}
}

void	bresenham_dy(t_fdf *fdf, t_bresenham *bre)
{

	bre->d = 2 * bre->dx - bre->dy;
	while (1)
	{
		pixel(fdf, bre->x0, bre->y0, WHITE);
		if (bre->y0 == bre->y1)
			break;
		if (bre->d < 0)
			bre->d = bre->d + 2 * bre->dx;
		else 
		{
			bre->x0 += bre->ix;
			bre->d = bre->d + (2 * bre->dx - 2 * bre->dy);
		}
		bre->y0 += bre->iy;
	}
}
