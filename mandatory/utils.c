/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tairribe <tairribe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:42:24 by tairribe          #+#    #+#             */
/*   Updated: 2022/12/23 19:43:26 by tairribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	usage(void)
{
	ft_putstr_fd("usage: fdf <filename>\n", 2);
	exit(1);
}

void	print_error(char *s)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(s, 2);
	exit(1);
}

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		exit (1);
	}
	return (fd);
}
