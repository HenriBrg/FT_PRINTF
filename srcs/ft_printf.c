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
  tab->precision = 0;
  tab->widthConfig     = 0;
  tab->precisionConfig = 0;
}

// TODO : gérer si ft_printf("%--10d") car on aura un -10 en width non ?
void control_config(t_printf *tab, char c)
{
  // Si 0 est spécifié pour un format entier (i, u, x, X, o, d) et qu’une spécification
  // de précision est également présente (par exemple, %04.d), le 0 est ignoré
  if (tab->precisionConfig && ft_strchr("dDioOuUxX", c))
    tab->zero = 0;
  // D'après mes observations, la précision l'emporte sur la width  car printf("%05.10d", -42) = -0000000042
  if (tab->precisionConfig)
    tab->widthConfig = tab->width = 0;
  // Si 0 et - apparaissent, le 0 est ignoré
  if (tab->minus)
    tab->zero = 0;
  // L’espace est ignoré si l’espace et des indicateurs + apparaissent
  if (tab->plus)
    tab->space = 0;
  //  flag ' ' results in undefined behavior with 'x' (idem pour 'o', 'O' et 'X')
  if (ft_strchr("oOxX", c) && tab->space)
    tab->space = 0;
  if (tab->space && ft_strchr("cCsS", c))
    tab->space = tab->width = tab->widthConfig = 0;
}

static void dispatch(t_printf *tab)
{
  tab->i++; // On saute le symbole %
  while (tab->i < (int)ft_strlen(tab->format) &&
         ft_strchr("-+ .0#0123456789hlzj", tab->format[tab->i]))
    setConfig(tab);
  control_config(tab, tab->format[tab->i]);
  if (ft_strchr("sSpdDioOuUxXcC", tab->format[tab->i]))
  {
    handleDisplay(tab, tab->format[tab->i]);
    apply_config(tab);
    ft_putendl(tab->output);
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
  ft_printf("\n   ---------- FT_PRINTF ------------\n\n");
  ft_printf("   FLAG - CHAR* via %%-10s avec 'Hello' : %-10s", "Hello");
  ft_printf("   FLAG - INT via %%- 10d avec   42     : %- 10d", 42);
  ft_printf("   FLAG - INT via %%-10d avec   42      : %-10d", 42);


  printf("\n   ----------- PRINTF --------------\n\n");
  printf("   FLAG - CHAR* via %%-10s avec 'Hello' : %-10s\n", "Hello");
  printf("   FLAG - INT via %%- 10d avec   42     : %- 10d\n", 42);
  printf("   FLAG - INT via %%-10d avec   42      : %-10d\n", 42);

  printf("\n");

  return (0);
}





/*


<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TEST APPLY CONFIG >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// WIDTH
ft_printf("   WIDTH     INT   via %%3d avec   12345   : %3d", 12345);
ft_printf("   WIDTH     INT   via %%10d avec  12345   : %10d", 12345);
ft_printf("   WIDTH     CHAR* via %%3s avec   'HELLO' : %3s", "HELLO");
ft_printf("   WIDTH     CHAR* via %%10s avec  'HELLO' : %10s", "HELLO");
ft_printf("   WIDTH HEX INT   via %%3x avec     42    : %3x", 42);
ft_printf("   WIDTH HEX INT   via %%#x avec     42    : %#x", 42);
ft_printf("   WIDTH HEX INT   via %%#010x avec   42   : %#010x", 42);


printf("   WIDTH     INT   via %%3d avec   12345   : %3d\n", 12345);
printf("   WIDTH     INT   via %%10d avec  12345   : %10d\n", 12345);
printf("   WIDTH     CHAR* via %%3s avec   'HELLO' : %3s\n", "HELLO");
printf("   WIDTH     CHAR* via %%10s avec  'HELLO' : %10s\n", "HELLO");
printf("   WIDTH HEX INT   via %%3x avec     42    : %3x\n", 42);
printf("   WIDTH HEX INT   via %%#x avec     42    : %#x\n", 42);
printf("   WIDTH HEX INT   via %%#010x avec   42   : %#010x\n", 42);

// PRECISION

ft_printf("   PRECISION CHAR* via %%.10s avec 'Hello' : %.10s", "Hello");
ft_printf("   PRECISION CHAR* via %%.1s avec 'Hello'  : %.1s", "Hello");
ft_printf("   PRECISION INT   via %%.0d avec    7     : %.0d", 7);
ft_printf("   PRECISION INT   via %%.10d avec  42     : %.10d", 42);
ft_printf("   PRECISION INT   via %%.10d avec -42     : %.10d", -42);
ft_printf("   PRECI HEX INT   via %%.3x avec     42   : %.3x", 42);
ft_printf("   PRECI HEX INT   via %%.5x avec     42   : %#.5x", 42);
ft_printf("   PRECI HEX INT   via %%#.10x avec   42   : %#.10x", 42);

printf("   PRECISION CHAR* via %%.10s avec 'Hello' : %.10s\n", "Hello");
printf("   PRECISION CHAR* via %%.1s avec 'Hello'  : %.1s\n", "Hello");
printf("   PRECISION INT   via %%.0d avec    7     : %.0d\n", 7);
printf("   PRECISION INT   via %%.10d avec  42     : %.10d\n", 42);
printf("   PRECISION INT   via %%.10d avec -42     : %.10d\n", -42);
printf("   PRECI HEX INT   via %%.3x avec     42   : %.3x\n", 42);
printf("   PRECI HEX INT   via %%.5x avec     42   : %#.5x\n", 42);
printf("   PRECI HEX INT   via %%#.10x avec   42   : %#.10x\n", 42);

// MELANGE de flags

ft_printf("   FLAG 0    INT   via %%010d avec  42     : %010d", 42);
ft_printf("   FLAG 0    INT   via %%010d avec  -42    : %010d", -42);
ft_printf("   FLAG ' '  INT   via %% 4d avec   42     : % 4d", 42);
ft_printf("   FLAG ' '  INT   via %% 4d avec   -42    : % 4d", -42);
ft_printf("   FLAG +    INT   via %%+d avec    42     : %+d", 42);

printf("   FLAG 0    INT   via %%010d avec  42     : %010d\n", 42);
printf("   FLAG 0    INT   via %%010d avec  -42    : %010d\n", -42);
printf("   FLAG ' '  INT   via %% 4d avec   42     : % 4d\n", 42);
printf("   FLAG ' '  INT   via %% 4d avec   -42    : % 4d\n", -42);
printf("   FLAG +    INT   via %%+d avec    42     : %+d\n", 42);




<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TEST CONVERTISSEURS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

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


<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TEST SET CONFIG >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

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
