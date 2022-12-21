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

int	free_mt(void **mt)
{
	int	i;

	i = 0;
	while(mt[i])
		free(mt[i++]);
	free(mt);
	return i;
}

int	ft_abs(int value)
{
	if (value < 0)
		return (-value);
	else
		return (value);
}