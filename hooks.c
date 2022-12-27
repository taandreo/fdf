/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:20:22 by tairribe          #+#    #+#             */
/*   Updated: 2022/12/27 04:01:13 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_control(t_fdf *fdf, int keycode)
{
	if (keycode == 'w')
	{
		fdf->line_size++;
		draw(fdf);
	}
	if (keycode == 's')
	{
		if (fdf->line_size < 1)
			return ;
		fdf->line_size--;
		draw(fdf);
	}
}

void	z_control(t_fdf *fdf, int keycode)
{
	if (keycode == 'z')
	{
		fdf->z += 0.1;
		draw(fdf);
	}
	if (keycode == 'x')
	{
		fdf->z -= 0.1;
		draw(fdf);
	}
}

void	up_vision(t_fdf *fdf)
{
	if (fdf->up)
		fdf->up = 0;
	else
		fdf->up = 1;
	draw(fdf);
}

int	key_press(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (keycode == KEY_ESC)
		exit_fdf((t_fdf *) param);
	if (ft_strrchr("ws", keycode))
		zoom_control(fdf, keycode);
	if (ft_strrchr("zx", keycode))
		z_control(fdf, keycode);
	if (ft_strrchr("f", keycode))
		up_vision(fdf);	
	return (0);
}
