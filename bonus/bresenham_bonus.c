/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:21:30 by tairribe          #+#    #+#             */
/*   Updated: 2022/12/28 02:21:09 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	bresenham_dx(t_fdf *fdf, t_bresenham *bre);
static void	bresenham_dy(t_fdf *fdf, t_bresenham *bre);

void	bresenham(t_fdf *fdf, t_point *src, t_point *dst)
{
	t_bresenham	bre;

	bre.x0 = src->x;
	bre.y0 = src->y;
	bre.x1 = dst->x;
	bre.y1 = dst->y;
	bre.c0 = src->color;
	bre.c1 = dst->color;
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

static void	bresenham_dx(t_fdf *fdf, t_bresenham *bre)
{
	bre->d = 2 * bre->dy - bre->dx;
	while (1)
	{
		pixel(fdf, bre->x0, bre->y0, bre->c0);
		if (bre->x0 == bre->x1)
			break ;
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

static void	bresenham_dy(t_fdf *fdf, t_bresenham *bre)
{
	bre->d = 2 * bre->dx - bre->dy;
	while (1)
	{
		pixel(fdf, bre->x0, bre->y0, bre->c0);
		if (bre->y0 == bre->y1)
			break ;
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
