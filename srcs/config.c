#include "../includes/ft_printf.h"

/*
** %[flags][width][.precision][size/length]type
*/


/*
** Pour gérer ça : printf("%+09d\n", 42); ===> +00000042
*/

static void setFlags(t_printf *tab)
{
  if (tab->format[tab->i] == '-')
    tab->minus = 1;
  else if (tab->format[tab->i] == '+')
    tab->plus = 1;
  else if (tab->format[tab->i] == ' ')
    tab->space = 1;
  else if (tab->format[tab->i] == '0')
    tab->zero = 1;
  else if (tab->format[tab->i] == '#')
    tab->hash = 1;
}

/*
** Pour gérer ça : printf("%10d\n", 12); ===> --------12 (tiret = espace)
*/
static void setWidth(t_printf *tab)
{
  if (tab->format[tab->i] != '0' && ft_isdigit(tab->format[tab->i]))
    tab->width = ft_atoi(&tab->format[tab->i]);
}

/*
**  Pour gérer ça : printf("%.10s\n", "abcdefghijklmn"); ==> abcdefghij
*/
static void setPrecision(t_printf *tab)
{
  if (tab->format[tab->i] != '.' )
    tab->precision = ft_atoi(&tab->format[tab->i + 1]);
}

/*
**  Pour gérer ça : char c = 0xf0; printf("%hhx", c);

*/
static void setSize(t_printf *tab)
{
  if (tab->format[tab->i] == 'h' )
    tab->h = 1;
  else if (tab->format[tab->i] == 'h' && tab->format[tab->i + 1] == 'h' )
    tab->hh = 1;
  else if (tab->format[tab->i] != 'l' )
    tab->l = 1;
  else if (tab->format[tab->i] != 'l' && tab->format[tab->i + 1] != 'l')
    tab->ll = 1;
  else if (tab->format[tab->i] != 'j' )
    tab->j = 1;
  else if (tab->format[tab->i] != 'z' )
    tab->z = 1;
}

void setConfig(t_printf *tab)
{
  setFlags(tab);
  setWidth(tab);
  setPrecision(tab);
  setSize(tab);
}
