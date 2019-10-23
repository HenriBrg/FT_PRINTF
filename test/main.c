#include "../includes/ft_printf.h"

int	main()
{
	int ret;

	ret = ft_printf("%.2c\n", NULL);
	printf("ret -->%d\n", ret);
	ret = ft_printf("@moulitest: %c\n", 0);
	printf("ret -->%d\n", ret);
	ret = ft_printf("%2c\n", 0);
	printf("ret -->%d\n", ret);
	ret = ft_printf("null %c and text\n", 0);
	printf("ret -->%d\n", ret);
	ret = ft_printf("% c\n", 0);
	printf("ret -->%d\n", ret);

	printf("\n\n ---------- \n\n");

	ret = printf("%.2c\n", NULL);
	printf("ret -->%d\n", ret);
	ret = printf("@moulitest: %c\n", 0);
	printf("ret -->%d\n", ret);
	ret = printf("%2c\n", 0);
	printf("ret -->%d\n", ret);
	ret = printf("null %c and text\n", 0);
	printf("ret -->%d\n", ret);
	ret = printf("% c\n", 0);
	printf("ret -->%d\n", ret);


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
