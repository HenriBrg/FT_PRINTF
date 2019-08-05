#include "../includes/ft_printf.h"

/*
** %[flags][width][.precision][size/length]type
*/

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
  tab->precision = 1;
}

static void dispatch(t_printf *tab)
{
  tab->i++; // On saute le symbole %
  while (tab->i < (int)ft_strlen(tab->format) &&
         ft_strchr("-+ .0#0123456789hlzj", tab->format[tab->i]))
    setConfig(tab);
  // showConfig(tab);
  if (ft_strchr("sSpdDioOuUxXcC", tab->format[tab->i]))
  {
    handleDisplay(tab, tab->format[tab->i]);
    if (tab->output)
      tab->returnSize += (int)ft_strlen(tab->output);
    resetConfig(tab);
    tab->i++; // On saute le symbole de conversion
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
  int                    a = -42;
  unsigned int           b = 42;
  long int               c = -100;
  unsigned long int      d = 100;
  long long int          e = -200;
  unsigned long long int f = 200;
  short                  g = -20;
  size_t                 h = 77;
  intmax_t               i = -3000000000;
  char                j[2] = "42";
  char                   k = 'c';
  char                  *l = "HELLO42STR";
  // L'a'  a une sizeof de 1
  // L'é'  a une sizeof de 2
  // L''  a une sizeof de 3
  // L'𝄞'  a une sizeof de 4
  wchar_t                m = L'é';
  wchar_t                *n = L"éab𝄞d";


  setlocale(LC_ALL, "");

  printf("---------- FT_PRINTF -----------\n");
  ft_printf("INT    via %%d   : %d", a);
  ft_printf("UINT   via %%u   : %u", b);
  ft_printf("LINT   via %%ld  : %ld", c);
  ft_printf("ULINT  via %%lu  : %lu", d);
  ft_printf("LLINT  via %%lld : %lld", e);
  ft_printf("ULLINT via %%llu : %llu", f);
  ft_printf("SHORT  via %%hd  : %hd", g);
  ft_printf("SIZE_T via %%zu  : %zu", h);
  ft_printf("IMAX_T via %%jd  : %jd", i);
  ft_printf("PTR    via %%p   : %p", j);
  ft_printf("CHAR   via %%c   : %c", k);
  ft_printf("STR    via %%s   : %s", l);
  ft_printf("WCHAR  via %%C   : %C", m);
  ft_printf("WCHAR* via %%S   : %S", n);

  printf("\n----------- PRINTF --------------\n");
  printf("INT    via %%d   : %d\n", a);
  printf("UINT   via %%u   : %u\n", b);
  printf("LINT   via %%ld  : %ld\n", c);
  printf("ULINT  via %%lu  : %lu\n", d);
  printf("LLINT  via %%lld : %lld\n", e);
  printf("ULLINT via %%llu : %llu\n", f);
  printf("SHORT  via %%hd  : %hd\n", g);
  printf("SIZE_T via %%zu  : %zu\n", h);
  printf("IMAX_T via %%jd  : %jd\n", i);
  printf("PTR    via %%p   : %p\n", j);
  printf("CHAR   via %%c   : %c\n", k);
  printf("STR    via %%s   : %s\n", l);
  printf("WCHAR  via %%C   : %C\n", m);
  printf("WCHAR* via %%S   : %S\n", n);

  return (0);
}





/*
________________________________________________________________________________

<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TEST de la fonction >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>




*/





/*

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
