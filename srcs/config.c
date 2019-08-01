#include "../includes/ft_printf.h"

/*
** %[flags][width][.precision][size/length]type
*/


/*
** Pour gérer : 0 - +  # et ' ' (espace)
** Exemple : printf("%+09d\n", 42); ===> +00000042
*/
static int setFlags(t_printf *tab)
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
** Pour gérer ça : printf("%10d\n", 12); ===> --------12 (tiret = espace)
*/
static int setWidth(t_printf *tab)
{
  if (ft_isdigit(tab->format[tab->i]))
  {
    tab->width = ft_atoi(&tab->format[tab->i]);
    tab->i += ft_strlen(ft_itoa(tab->width));
    return (1);
  }
  return (0);
}

/*
**  setPrecision() gère ça : printf("%.10s\n", "abcdefghijklmn"); ==> abcdefghij
*/
static int setPrecision(t_printf *tab)
{
  if (tab->format[tab->i] == '.' )
  {
    tab->i++;
    tab->precision = ft_atoi(&tab->format[tab->i]);
    tab->i += ft_strlen(ft_itoa(tab->precision));
    return (1);
  }
  return (0);
}

/*
**  setSize() gére ça : char c = 0xf0; printf("%hhx", c);
*/
static int setSize(t_printf *tab)
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


void showConfig(t_printf *tab)
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
  printf("precision : %d\n", tab->precision );
}


void setConfig(t_printf *tab)
{
  if (setFlags(tab) == 1)
  {
    // Hiérarchie des flags ?
    // if (fab->plus)
  	// 	fab->space = 0;
    return ;
  }
  if (setWidth(tab) == 1)
    return ;
  if (setPrecision(tab) == 1)
    return ;
  if (setSize(tab) == 1)
  {
    // A voir si nécessaire :
    // while (ft_strchr("hljz", tab->format[tab->i]))
		// 	tab->i++;
    return ;
  }
  // L'idée c'est de validé la config, faut pas qu'il y ai 2 fois hh hh par exemple, ou autre forme de doublons, etc ...
  // Hiérarchie de priorité dans les flags ? +-# 0 ?
  // TODO : fonction validConfig()


  // EN GROS IL FAUT QUE LA CONFIG QUI ARRIVE DANS handleDisplay() soit clean
  // de manière à ne générer aucune erreur dans handleDisplay()
}
