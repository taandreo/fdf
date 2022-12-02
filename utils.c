# include "fdf.h"

void	usage()
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