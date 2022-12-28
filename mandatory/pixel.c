/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:39:19 by tairribe          #+#    #+#             */
/*   Updated: 2022/12/23 19:53:56 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x > fdf->win_width || y < 0 || y > fdf->win_height)
		return ;
	pixel = fdf->img->data + (fdf->img->size_line * y) + \
		((fdf->img->pixels / 8) * x);
	*(unsigned int *)pixel = color;
}
