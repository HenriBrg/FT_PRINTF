#include "../includes/ft_printf.h"

int	main()
{

	// write(1 , "\0", 1);
	printf("-->%.2c\n", NULL);
	ft_printf("-->%.2c\n", NULL);
	return (0);
}
