#include "../includes/ft_printf.h"

/*
** %[flags][width][.precision][size/length]type
*/

static void resetConfig(t_printf *tab)
{
  tab->minus     = 0;
  tab->plus      = 0;
  tab->space     = 0;
  tab->zero      = 0;
  tab->hash      = 0;
  tab->h         = 0;
  tab->hh        = 0;
  tab->l         = 0;
  tab->ll        = 0;
  tab->j         = 0;
  tab->z         = 0;
  tab->width     = 0;
  tab->precision = 0;
}

static void dispatch(t_printf *tab)
{
  tab->i++;
  while (tab->i < (int)ft_strlen(tab->format) &&
         ft_strchr("-+ .0#0123456789hlzj", tab->format[tab->i]))
    setConfig(tab);
  showConfig(tab);
  if (ft_strchr("sSpdDioOuUxXcC", tab->format[tab->i]))
  {
    handleDisplay(tab);
    resetConfig(tab);
    printf("Config reset\n");
  }
}

int ft_printf(const char *format, ...)
{
  t_printf *tab;

  if ((tab = malloc(sizeof(t_printf))) == 0)
    return (-1);
  tab->i = tab->returnSize = 0;
  va_start(tab->args, format);
  tab->format = (char*)format;
  resetConfig(tab);
  while (tab->format[tab->i] != '\0')
  {
    if (tab->format[tab->i] == '%' && tab->format[tab->i + 1] == '%')
    {
      write(1, "%", 1);
      tab->i += 2;
      tab->returnSize += 1;
    }
    else if (tab->format[tab->i] == '%')
      dispatch(tab);
    else
    {
      write(1, &tab->format[tab->i], 1);
      tab->returnSize += 1;
      tab->i++;
    }
  }
  return (tab->returnSize);
}

int main()
{
  ft_printf("Hello%+lld %10");
  printf("\n");
  return (0);
}

/* TEST du parsing :

ft_printf("Hello%"); aucune config
ft_printf("Hello%5"); width 5
ft_printf("Hello%05"); zero 1 et width 5
ft_printf("Hello%+5"); plus 1 et width 5
ft_printf("Hello%-5"); minus 1 et width 5
ft_printf("Hello% 5"); space 1 et width 5
ft_printf("Hello%#5"); hash 1 et width 5

ft_printf("Hello%.10"); precision 10
ft_printf("Hello%-15.10"); minus 1 width 15 precision 10

ft_printf("Hello%hh"); hh 1
ft_printf("Hello%ll"); ll 1
ft_printf("Hello%h"); h 1
ft_printf("Hello%l"); l 1
ft_printf("Hello%j"); j 1
ft_printf("Hello%z"); z 1

ft_printf("Hello%#hh"); hash 1 et hh 1
ft_printf("Hello%#ll"); hash 1 et ll 1
ft_printf("Hello%#h"); hash 1 et h 1
ft_printf("Hello%#l"); hash 1 et l 1
ft_printf("Hello%#j"); hash 1 et j 1
ft_printf("Hello%#z"); hash 1 et z 1

ft_printf("Hello%.10ll"); ll 1 et precision 10
ft_printf("Hello%+ll"); ll 1 et plus 1

ft_printf("Hello%+lld %10"); Config 1 : plus 1, ll 1 et Config 2 : width 10
*/

/*

ft_printf("value: %d\n", i);
ft_printf("%s, %s!\n", "Hello", "world");
ft_printf("Hello World!\n");
ft_printf("%s", "This is ");
ft_printf("%.*s\n", 9, "ft_printf and ft_dprintf");
ft_printf("%d\n", 123);
ft_printf("%05d\n", 42);
ft_printf("%+09d\n", 42);
ft_printf("%u\n", UINT_MAX);
ft_printf("%#b\n", 256);
ft_printf("%#o\n", 1039);
ft_printf("%#X\n", 16417188);
ft_printf("%p\n", &i);

*/
