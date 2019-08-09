#include "../includes/ft_printf.h"

/*
** Pour débugger
*/

void show_config(t_printf *tab)
{
  printf("\n");
  printf("Format    : %s\n", tab->format    );
  printf("Format[i] : %c\n", tab->format[tab->i]);
  printf("i         : %d\n", tab->i         );
  printf("minus     : %d\n", tab->minus     );
  printf("plus      : %d\n", tab->plus      );
  printf("space     : %d\n", tab->space     );
  printf("zero      : %d\n", tab->zero      );
  printf("hash      : %d\n", tab->hash      );
  printf("h         : %d\n", tab->h         );
  printf("hh        : %d\n", tab->hh        );
  printf("l         : %d\n", tab->l         );
  printf("ll        : %d\n", tab->ll        );
  printf("j         : %d\n", tab->j         );
  printf("z         : %d\n", tab->z         );
  printf("width     : %d\n", tab->width     );
  printf("widthConf : %d\n", tab->widthConfig     );
  printf("precision : %d\n", tab->precision );
  printf("preciConf : %d\n", tab->precisionConfig );
}

/*
**  set_flags active la valeur du flag en structure
**  s'il est détecté et incrémente i
*/
static int set_flags(t_printf *tab)
{
  if (tab->format[tab->i] == '-' && tab->i++)
    return ((tab->minus = 1));
  else if (tab->format[tab->i] == '+' && tab->i++)
    return ((tab->plus = 1));
  else if (tab->format[tab->i] == ' ' && tab->i++)
    return ((tab->space = 1));
  else if (tab->format[tab->i] == '0' && tab->i++)
    return ((tab->zero = 1));
  else if (tab->format[tab->i] == '#' && tab->i++)
    return ((tab->hash = 1));
  return (0);
}


/*
** set_width() intervient si on tombe sur un chiffre
** avec atoi et incrément i de la taille du nombre
*/

static int set_width(t_printf *tab)
{
  if (ft_isdigit(tab->format[tab->i]))
  {
    while (tab->format[tab->i] == '0')
      tab->i++;
    tab->width = ft_atoi(&tab->format[tab->i]);
    tab->i += ft_strlen(ft_itoa(tab->width));
    tab->widthConfig = 1;
    return (1);
  }
  return (0);
}

/*
**  set_precision() gère ça la précision si un . est détecté
**  On saute le . puis on atoi le nombre qui suit et incrémente i
**  par de la taille de ce nombre
**  Le while intervient pour gérer les éventuels 0 dans ft_printf("%.09s", "hi low");
**  afin que i soit correctement incrémenté, sans quoi, dans le cas ci dessus,
**  i serait incrémenté seulement de 1 car strlen atoi (09) = 1
*/

static int set_precision(t_printf *tab)
{
  if (tab->format[tab->i] == '.')
  {
    tab->i++;
    while (tab->format[tab->i] == '0')
      tab->i++;
    if (!ft_isdigit(tab->format[tab->i]))
    {
      tab->precisionConfig = 1;
      tab->precision = 0;
      return (1);
    }
    tab->precision = ft_atoi(&tab->format[tab->i]);
    tab->i += ft_strlen(ft_itoa(tab->precision));
    tab->precisionConfig = 1;
    return (1);
  }
  return (0);
}

/*
**  setSize() gére les détection des flags (h, hh, l, ll, j, z)
**  et incrémente tab->i de la taille du flag
*/

static int set_size(t_printf *tab)
{
  if (tab->format[tab->i] == 'h' && tab->format[tab->i + 1] == 'h'
      && tab->i++ && tab->i++)
    return ((tab->hh = 1));
  else if (tab->format[tab->i] == 'l' && tab->format[tab->i + 1] == 'l'
      && tab->i++ && tab->i++)
    return ((tab->ll = 1));
  else if (tab->format[tab->i] == 'h' && tab->i++)
    return ((tab->h = 1));
  else if (tab->format[tab->i] == 'l' && tab->i++)
    return ((tab->l = 1));
  else if (tab->format[tab->i] == 'j' && tab->i++)
    return ((tab->j = 1));
  else if (tab->format[tab->i] == 'z' && tab->i++)
    return ((tab->z = 1));
  return (0);
}


/*
** RAS
*/

void set_config(t_printf *tab)
{
  if (set_flags(tab) == 1)
    return ;
  if (set_width(tab) == 1)
    return ;
  if (set_precision(tab) == 1)
    return ;
  if (set_size(tab) == 1)
    return ;
}
