#include "../includes/ft_printf.h"

void apply_precision(t_printf *tab, char c)
{
  int i;
  int size;
  int negative;
  char *tmp;

  if (ft_strchr("diouxX", c) && tab->precisionConfig
                             && tab->precision > (int)ft_strlen(tab->output))
  {
      size = ft_strlen(tab->output);
      negative = (tab->output[0] == '-') ? 1 : 0;
      tmp = ft_strnew(size + (tab->precision - size) + negative);
      i = -1;
      if (negative && i++)
        tmp[0] = '-';
      while (++i < (tab->precision - size + negative + negative)) // Ca fonctionne mais je comprends pas pourquoi il faut mettre deux fois le + negative
        tmp[i] = '0';
      tab->output = ft_strjoin(tmp, tab->output + negative);
      free(tmp);
  }
  else if (c == 's' && tab->precisionConfig == 1)
    tab->output = strndup(tab->output, tab->precision);
}

void apply_width(t_printf *tab)
{
  int i;
  int size;
  char c;
  char *tmp;

  c = (tab->zero) ? '0' : ' ';
  if (tab->width > (int)ft_strlen(tab->output))
  {
    size = ft_strlen(tab->output);
    tmp = ft_strnew(size + (tab->width - size));
    i = -1;
    while (++i < tab->width - size)
      tmp[i] = c;
    tab->output = ft_strjoin(tmp, tab->output);
    free(tmp);
  }
}

// void flags(t_printf *tab)
// {
//
// }

void apply_config(t_printf *tab)
{
  // TODO : gérer si ft_printf("%--10d") car on aura un -10 en width non ?
  if (tab->precisionConfig == 1 && ft_strchr("diouxXsS", tab->format[tab->i]))
    apply_precision(tab, tab->format[tab->i]);
  if (tab->widthConfig == 1)
    apply_width(tab);
}
