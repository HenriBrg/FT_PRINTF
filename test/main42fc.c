#include "../includes/ft_printf.h"

int	main()
{

	printf("\n\n  ------------------------\n\n");


	ft_printf("%.2c\n", NULL);
	ft_printf("@moulitest: %c\n", 0);
	ft_printf("%2c\n", 0);
	ft_printf("null %c and text\n", 0);
	ft_printf("% c\n", 0);

	printf("  ------------------------\n");

	printf("%.2c\n", NULL);
	printf("@moulitest: %c\n", 0);
	printf("%2c\n", 0);
	printf("null %c and text\n", 0);
	printf("% c\n", 0);

	return (0);
}

// make && gcc -w test/main42fc.c -L. libftprintf.a && ./a.out | cat -e
