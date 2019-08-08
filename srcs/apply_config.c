#include "../includes/ft_printf.h"

/*
** La fonction prefix n'intervient que si
** 1 > Il y a une width et le flag '0' est présent
** 2 > Il y a une précision
** S'il y a une width sans flag '0', il n'y a pas besoin de mettre de prefixe
** au début
*/

char *prefix(t_printf *tab, char c)
{
  char *prefix;

  // Préfixes possibles : - + 0 0x 0X et ' ' et uniquement sur les nombres
  if (ft_strchr("dDioOuUxX", c) == NULL)
    return (0);
  if (tab->output[0] == '-')
    prefix = ft_strdup("-");
  else if (tab->output[0] == '+')
    prefix = ft_strdup("+");
  else if ((c == 'o' || c == 'O') && tab->output[0] == '0')
    prefix = ft_strdup("0");
  else if (tab->output[0] == ' ')
    prefix = ft_strdup(" ");
  else if (tab->output[0] == '0' && tab->output[1] == 'x')
    prefix = ft_strdup("0x");
  else if (tab->output[0] == '0' && tab->output[1] == 'X')
    prefix = ft_strdup("0X");
  else
    prefix = NULL;
  return (prefix);
}

/*
** apply_precision intervient sur les nombres SI leur taille est inférieur à la précision donnée
** S'il y a un prefixe (ex : 0x), il est stocké dans strprefix
** La précision ne prend pas en compte le préfixe : exemple :
** PRECI HEX INT   via %.5x avec     42   : 0x0002a (on a 0002a de taille 5 = précision) puis le préfix
**
** Si on a un string, tab->precision caractère sont copiés et il peut donc y avoir un troncation
** A la différence de la width, la précision limite le nombre de chiffres sortant (une sorte d'arrondi), et non le nombre total de caractère (ce qui fait que l'éventuel préfixe est exclu)
*/

void apply_precision(t_printf *tab, char c)
{
  int i;
  int size;
  int prefix_size;
  char *tmp;
  char *strprefix;

  if (ft_strchr("dDiouUxX", c) && tab->precisionConfig
                               && tab->precision > (int)ft_strlen(tab->output))
  {
    strprefix = prefix(tab, c);
    size = ft_strlen(tab->output);
    tmp = ft_strnew(size + (tab->precision - size));
    i = -1;
    prefix_size = (strprefix != 0) ? ft_strlen(strprefix) : 0;
    while (++i < tab->precision - size + prefix_size)
      tmp[i] = '0';
    if (strprefix != 0)
      tmp = ft_strjoin(strprefix, tmp);
    size = (strprefix != 0) ? ft_strlen(strprefix) : 0;
    tab->output = ft_strjoin(tmp, tab->output + size);
    free(tmp);
  }
  else if ((c == 's' || c == 'S') && tab->precisionConfig == 1) // Pas sur les wchar_t* soit correctement gérés ici
    tab->output = ft_strndup(tab->output, tab->precision);
}

/*
** apply_width intervient sur les nombres et string SI leur taille est inférieur à la width donnée
** Elle détermine la taille maximale de l'output (au sens de strlen(output)) et prend donc en compte la taille de l'éventuel préfixe (à l'inverse de la précision)
** Si le flag 0 est activé, le remplissage se fera par des 0 plutot que par des ' '
*/


void apply_width(t_printf *tab)
{
  int i;
  int size;
  char c;
  char *tmp;
  char *strprefix;

  // TODO : gérer tous les préfixes possibles (- + 0 0x 0X ...)
  strprefix = (tab->zero == 1) ? prefix(tab, tab->format[tab->i]) : 0;
  if (tab->width > (int)ft_strlen(tab->output))
  {
    c = (tab->zero == 1) ? '0' : ' ';
    size = ft_strlen(tab->output);
    tmp = ft_strnew(size + (tab->width - size));
    i = -1;
    while (++i < tab->width - size)
      tmp[i] = c;
    if (strprefix != 0)
      tmp = ft_strjoin(strprefix, tmp);
    size = (strprefix != 0) ? ft_strlen(strprefix) : 0;
    tab->output = ft_strjoin(tmp, tab->output + size);
    free(tmp);
  }
}

/*
** Les flags + ' ' # sont gérés dans apply_flags
** (Le flag '-' sera géreé tout à la fin et le flag '0' sera géré dans width())
*/

void apply_flags(t_printf *tab, char c)
{
  if (tab->plus && ft_strchr("idD", c) && tab->output[0] != '-')
    tab->output = ft_strjoin("+", tab->output);
  else if (tab->space && ft_strchr("idD", c) && tab->output[0] != '-')
      tab->output = ft_strjoin(" ", tab->output);
  else if (tab->hash && ft_strchr("xXoO", c))
  {
    if (c == 'o' || c == 'O')
      tab->output = ft_strjoin("0", tab->output);
    else if (c == 'x')
      tab->output = ft_strjoin("0x", tab->output);
    else if (c == 'X')
      tab->output = ft_strjoin("0X", tab->output);
  }
}

/* Ordre d'application de la config :
** 1/ Flags + (ajoute + ou -), flag ' ' (ajoute +) et flag # (ajoute 0, 0x, 0X)
** 2/ Width (width combiné ou non au flag 0) OU Précision (qui par défaut remplit par 0)
** 3/ Flag -
*/

void apply_config(t_printf *tab)
{
  int i;
  int place;
  int min_plus;
  char *tmp;

  apply_flags(tab, tab->format[tab->i]);
  if (tab->precisionConfig == 1 && ft_strchr("diouxXsScC", tab->format[tab->i]))
    apply_precision(tab, tab->format[tab->i]);
  else if (tab->widthConfig == 1)
    apply_width(tab);
  // Gestion du flag '-' :
  if (tab->minus)
  {
    i = -1;
    place = min_plus = 0;
    if (tab->space && ft_strchr("idD", tab->format[tab->i])
                   && !ft_strchr(tab->output, '-'))
      min_plus = 1;
    while (tab->output[++i] == ' ')
      place++;
    tmp = ft_memset(ft_strnew(place + 1), ' ', place);
    tab->output = ft_strjoin(tab->output + place - min_plus, tmp + min_plus);
  }
}
