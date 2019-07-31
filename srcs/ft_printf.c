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
  tab->flags     = 0;
  tab->width     = 0;
  tab->precision = 0;
  tab->h         = 0;
  tab->hh        = 0;
  tab->l         = 0;
  tab->ll        = 0;
  tab->j         = 0;
  tab->z         = 0;
}

static void dispatch(t_printf *tab)
{
  while (tab->format[tab->i] != '\0')
  {
    if (ft_strchr("-+ .0#0123456789hlzj", tab->format[tab->i]))
      setConfig(tab);
    else if (ft_strchr("sSpdDioOuUxXcC", tab->format[tab->i]))
    {
      handleDisplay(tab);
      resetConfig(tab);
      tab->i++;
    }
    tab->i++;
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
      tab->returnSize += write(1, &tab->format[tab->i++], 1);
  }
  return (tab->i);
}









int main()
{
  ft_printf("He%llo");
  return (0);
}

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
