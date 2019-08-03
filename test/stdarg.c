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
# include <stdint.h>

void f (int n, ...)
{
   PCHAR a;
   va_list va;
   va_start (va, n);

   char *s1 = va_arg(va, char*);
   char *s2 = va_arg(va, char*);
   char ab =  va_arg(va, unsigned int);
   printf("%s\n", s1);
   printf("%s\n", s2);
   printf("%hhd\n", ab);
   va_end (va);
}

int main()
{
  unsigned char a = 42;
  f(42, "Hello", "42STR", a);
  return (0);
}
