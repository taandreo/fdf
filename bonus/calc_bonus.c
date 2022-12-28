/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:50:54 by tairribe          #+#    #+#             */
/*   Updated: 2022/12/28 02:21:25 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	centralize_before(t_fdf *fdf, t_point *po)
{
	po->x -= (fdf->x * fdf->line_size) / 2;
	po->y -= (fdf->y * fdf->line_size) / 2;
}

void	centralize_after(t_fdf *fdf, t_point *po)
{
	po->x += fdf->win_width / 2;
	po->y += (fdf->win_height + (fdf->y * fdf->line_size) / 2) / 2;
}

void	zoom(t_fdf *fdf, t_point *po)
{
	po->x *= fdf->line_size;
	po->y *= fdf->line_size;
}

void	rotate_z(t_point *po, float angle)
{
	float	x;
	float	y;

	x = po->x;
	y = po->y;
	po->x = x * cos(angle) - y * sin(angle);
	po->y = x * sin(angle) + y * cos(angle);
}

void	rotate_x(t_point *po, float angle, float zm)
{
	float	y;
	float	z;

	y = po->y;
	z = po->z;
	po->y = y * cos(angle) - (z * sin(angle) * zm);
	po->z = y * sin(angle) + (z * cos(angle) * zm);
}
