# define INT int
# define PINT int*

# define UINT unsigned int

# define LONG long int
# define LLONG long long int

# define SHORT short
# define DOUBLE double

# define CHAR char
# define PCHAR char*

typedef struct s_printf {
  char *str;
  void *example;
}              t_printf;

# include <stdarg.h>
# include <stdio.h>

void f (int n, ...)
{
   PCHAR a;
   va_list va;
   va_start (va, n);

   char *s1 = va_arg(va, PCHAR);
   char *s2 = va_arg(va, PCHAR);
   printf("%s\n", s1);
   printf("%s\n", s2);
   va_end (va);
}

int main()
{
  f(42, "Hello", "42");
  return (0);
}
