#include "libft/include/libft.h"
#include <stdio.h>

int	main(void)
{
	int	i;

	i = ft_atoi_base("0x012FF", 10);
	printf("i: %i\n", i);
}