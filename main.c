#include "./includes/ft_printf.h"

int	main()
{

	printf("%.5p\n", 0);
	ft_printf("%.5p\n", 0);

	/*
	char *s = "Hey";

	ft_printf("|%*s|\n", 10, s);
	ft_printf("|%.*d|\n", 7, 12345);
	ft_printf("|%*.d|\n", 7, 123456789);


	printf("------\n");

	printf("|%*s|\n", 10, s);
	printf("|%.*d|\n", 7, 12345);
	printf("|%*.d|\n", 7, 123456789);
	*/
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
