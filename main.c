#include "./includes/ft_printf.h"

int	main()
{

	ft_printf("%.0p, %.p\n", 0, 0);
	ft_printf("%.p, %.0p\n", 0, 0);

	printf("\n------\n\n");

	printf("%.0p, %.p\n", 0, 0);
	printf("%.p, %.0p\n", 0, 0);

	return (0);
}

/* TESTS QUI FONT CHIER

	ft_printf("-->%.0p, %.p\n", 0, 0);
	ft_printf("-->%.p, %.0p\n", 0, 0);
	test_zero -> printf("%c", 0)
	in_width_c -> printf("{%3c}", 0)
	test_hex_c_zero -> printf("%#c", 0)
	printf("%.c", 0)
	printf("%.0p, %.p", 0, 0)
	printf("%.p, %.0p", 0, 0)
*/
