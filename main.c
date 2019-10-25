#include "./includes/ft_printf.h"

int	main()
{

	//printf("1-%p\n", 0);
	//printf("2-{%5p}\n", 0);
	printf("3-%.5p\n", 0);
	printf("4-%.0p, %.p\n", 0, 0);
	printf("5-%.p, %.0p\n", 0, 0);
	//printf("6-%.0d\n", 0);
	printf("\n");
	//ft_printf("1-%p\n", 0);
	//ft_printf("2-{%5p}\n", 0);
	ft_printf("3-%.5p\n", 0);
	ft_printf("4-%.0p, %.p\n", 0, 0);
	ft_printf("5-%.p, %.0p\n", 0, 0);
	//ft_printf("6-%.0d\n", 0 );

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
