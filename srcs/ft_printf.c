#include "../includes/ft_printf.h"

static void resetConfig(t_printf *tab)
{
  tab->output    = 0;
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
  tab->widthConfig     = 0;
  tab->precisionConfig = 0;
}

/*
** 1) Si 0 est spécifié pour un format entier (i, u, x, X, o, d) et qu’une spécification
** de précision est également présente (par exemple, %04.d), le 0 est ignoré
**
** 2) D'après mes observations, la précision l'emporte sur la width  car printf("%05.10d", -42) = -0000000042
**
** 3) Si 0 et - apparaissent, le 0 est ignoré
**
** 4) L’espace est ignoré si l’espace et des indicateurs + apparaissent
**
** 5) flag ' ' results in undefined behavior with 'x' (idem pour 'o', 'O' et 'X')
**
** 6) Si flag ' ' et que conversion en string ou char, le flag ' ' est ignoré
*/

static void control_config(t_printf *tab, char c)
{
  if (tab->precisionConfig && ft_strchr("dDioOuUxXb", c))
    tab->zero = 0;
  if (tab->minus)
    tab->zero = 0;
  if (tab->plus)
    tab->space = 0;
  if (ft_strchr("oOxX", c) && tab->space)
    tab->space = 0;
}

/*
** 1) On saute le %
** 2) On itère sur chaque char de configuration possible ("-+ .0#0123456789hlzj")
** 3) Si on en trouve un, on appel setConfig() qui va stocker la config dans la structure tab
**    Au sein de la fonction setConfig, il peut y avoir des jump (incrémentation de tab->i)
**    lorsqu'il faut aller récupérer un nombre après le flag '0' par exemple
** 4) Après on contrôle la cohérence de la config, s'il y a des instructions incompatible, on corrige dans control_config
** Note : on test ensuite si on est pas à la fin du string format, sinon on segfaulterai par la suite
** 5) On arrive sur le symbole de conversion, et appel handleDisplay qui stock l'output brut dans la structure
** 6) On applique à cet tab->output la config et on le print
** 7) Si l'output n'est pas nul, on incrémente returnSize de strlen(tab->output)
** 8) On reset la config pour les éventuels prochaines conversions puis on saute le symbole
**
** IDEE : faire un if (ft_strchr("sSpdDioOuUxXcCb%", tab->format[tab->i]) == 0
**                       && ft_strchr("-+ .0#0123456789hlzj", tab->format[tab->i]) == 0
**                         return ; // car on est plus sur de la config et le char qui suit la fin de la config n'est pas un convertisseur
**
*/

static void dispatch(t_printf *tab)
{
  tab->i++;

  while (tab->i < (int)ft_strlen(tab->format) &&
         ft_strchr("-+ .0#0123456789hlzj", tab->format[tab->i]))
    set_config(tab);
  control_config(tab, tab->format[tab->i]);
  if (tab->format[tab->i] == '\0')
    return ;
  if (ft_strchr("sSpdDioOuUxXcCb%", tab->format[tab->i]))
  {
    handle_display(tab, tab->format[tab->i]);
    apply_config(tab);
    ft_putstr(tab->output);
    if (tab->output)
      tab->returnSize += (int)ft_strlen(tab->output);
    resetConfig(tab);
    tab->i++;
  }
}

/*
** On itère sur *format et dès que l'on détecte un %
** on appel dispatch() (sauf si %%)
*/

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
