# Très bonne explication des Makefile :

# 	https://stackoverflow.com/questions/3220277/what-do-the-makefile-symbols-and-mean
# 	https://stackoverflow.com/questions/54854128/use-of-o-c-in-makefile

NAME = libftprintf.a

SRCS = srcs/ft_printf.c srcs/set_config.c srcs/display.c srcs/apply_config.c \
	   srcs/utils.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

# ifndef VERBOSE
# .SILENT:
# endif

all: $(NAME)

.c.o:
	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C libft
	cp libft/libft.a $(NAME)
	ar rcs $(NAME) $(OBJS)

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
