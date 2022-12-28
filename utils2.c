/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:42:07 by tairribe          #+#    #+#             */
/*   Updated: 2022/12/28 00:06:42 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	free_mt(void **mt)
{
	int	i;

	i = 0;
	while (mt[i])
		free(mt[i++]);
	free(mt);
	return (i);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	ft_abs(int value)
{
	if (value < 0)
		return (-value);
	else
		return (value);
}

int	get_mt_size(void **mt)
{
	int	i;

	i = 0;
	while (mt[i])
		i++;
	return (i);
}
