#include "fdf.h"

int main(void)
{
	void *mlx_ptr;
	void *win_ptr;
	mlx_ptr = mlx_init();

	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "Hello World");
	printf("%p\n", win_ptr);
	ft_strdup("pato");
	return (0);
}

