#include "../includes/ft_printf.h"

int main()
{

  printf("\n\n<<<<<<<<<<<<<<<<<<<< TEST CONVERTISSEURS >>>>>>>>>>>>>>>>>>>>>");
  printf("\n\n\n");

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
  //wchar_t                m = L'é';
  //wchar_t                *n = L"éab𝄞d";
  //setlocale(LC_ALL, "");

  printf("\n   ---------- FT_PRINTF -----------\n");
  ft_printf("   INT    via %%d   : %d\n", a);
  ft_printf("   UINT   via %%u   : %u\n", b);
  ft_printf("   LINT   via %%ld  : %ld\n", c);
  ft_printf("   ULINT  via %%lu  : %lu\n", d);
  ft_printf("   LLINT  via %%lld : %lld\n", e);
  ft_printf("   ULLINT via %%llu : %llu\n", f);
  ft_printf("   SHORT  via %%hd  : %hd\n", g);
  ft_printf("   SIZE_T via %%zu  : %zu\n", h);
  ft_printf("   IMAX_T via %%jd  : %jd\n", i);
  ft_printf("   PTR    via %%p   : %p\n", j);
  ft_printf("   CHAR   via %%c   : %c\n", k);
  ft_printf("   STR    via %%s   : %s\n", l);
  //ft_printf("   WCHAR  via %%C   : %C\n", m);
  //ft_printf("   WCHAR* via %%S   : %S\n", n);
  ft_printf("   OCT INT   via %%o avec     42     : %o\n", 42);
  ft_printf("   OCT INT   via %%o avec     -42    : %o\n", -42);
  ft_printf("   HEX INT   via %%x avec     42     : %x\n", 42);
  ft_printf("   HEX INT   via %%x avec     -42    : %x\n", -42);




  printf("\n   ----------- PRINTF --------------\n");
  printf("   INT    via %%d   : %d\n", a);
  printf("   UINT   via %%u   : %u\n", b);
  printf("   LINT   via %%ld  : %ld\n", c);
  printf("   ULINT  via %%lu  : %lu\n", d);
  printf("   LLINT  via %%lld : %lld\n", e);
  printf("   ULLINT via %%llu : %llu\n", f);
  printf("   SHORT  via %%hd  : %hd\n", g);
  printf("   SIZE_T via %%zu  : %zu\n", h);
  printf("   IMAX_T via %%jd  : %jd\n", i);
  printf("   PTR    via %%p   : %p\n", j);
  printf("   CHAR   via %%c   : %c\n", k);
  printf("   STR    via %%s   : %s\n", l);
  //printf("   WCHAR  via %%C   : %C\n", m);
  //printf("   WCHAR* via %%S   : %S\n", n);
  printf("   OCT INT   via %%o avec     42     : %o\n", 42);
  printf("   OCT INT   via %%o avec     -42    : %o\n", -42);
  printf("   HEX INT   via %%x avec     42     : %x\n", 42);
  printf("   HEX INT   via %%x avec     -42    : %x\n", -42);

  printf("\n\n<<<<<<<<<<<<<<<<<<<< TEST APPLY CONFIG >>>>>>>>>>>>>>>>>>>");
  printf("\n\n\n");

  // WIDTH
  printf("\n   ---------- FT_PRINTF -----------\n");
  ft_printf("   WIDTH     INT   via %%3d avec   12345   : %3d\n", 12345);
  ft_printf("   WIDTH     INT   via %%10d avec  12345   : %10d\n", 12345);
  ft_printf("   WIDTH     CHAR* via %%3s avec   'HELLO' : %3s\n", "HELLO");
  ft_printf("   WIDTH     CHAR* via %%10s avec  'HELLO' : %10s\n", "HELLO");
  ft_printf("   WIDTH HEX INT   via %%3x avec     42    : %3x\n", 42);
  ft_printf("   WIDTH HEX INT   via %%#x avec     42    : %#x\n", 42);
  ft_printf("   WIDTH HEX INT   via %%#010x avec   42   : %#010x\n", 42);

  printf("\n   ---------- PRINTF -----------\n");
  printf("   WIDTH     INT   via %%3d avec   12345   : %3d\n", 12345);
  printf("   WIDTH     INT   via %%10d avec  12345   : %10d\n", 12345);
  printf("   WIDTH     CHAR* via %%3s avec   'HELLO' : %3s\n", "HELLO");
  printf("   WIDTH     CHAR* via %%10s avec  'HELLO' : %10s\n", "HELLO");
  printf("   WIDTH HEX INT   via %%3x avec     42    : %3x\n", 42);
  printf("   WIDTH HEX INT   via %%#x avec     42    : %#x\n", 42);
  printf("   WIDTH HEX INT   via %%#010x avec   42   : %#010x\n", 42);

  // PRECISION
  printf("\n   ---------- FT_PRINTF -----------\n");
  ft_printf("   PRECISION CHAR* via %%.10s avec 'Hello' : %.10s\n", "Hello");
  ft_printf("   PRECISION CHAR* via %%.1s avec 'Hello'  : %.1s\n", "Hello");
  ft_printf("   PRECISION INT   via %%.0d avec    7     : %.0d\n", 7);
  ft_printf("   PRECISION INT   via %%.10d avec  42     : %.10d\n", 42);
  ft_printf("   PRECISION INT   via %%.10d avec -42     : %.10d\n", -42);
  ft_printf("   PRECI HEX INT   via %%.3x avec     42   : %.3x\n", 42);
  ft_printf("   PRECI HEX INT   via %%.5x avec     42   : %#.5x\n", 42);
  ft_printf("   PRECI HEX INT   via %%#.10x avec   42   : %#.10x\n", 42);

  printf("\n   ---------- PRINTF -----------\n");
  printf("   PRECISION CHAR* via %%.10s avec 'Hello' : %.10s\n", "Hello");
  printf("   PRECISION CHAR* via %%.1s avec 'Hello'  : %.1s\n", "Hello");
  printf("   PRECISION INT   via %%.0d avec    7     : %.0d\n", 7);
  printf("   PRECISION INT   via %%.10d avec  42     : %.10d\n", 42);
  printf("   PRECISION INT   via %%.10d avec -42     : %.10d\n", -42);
  printf("   PRECI HEX INT   via %%.3x avec     42   : %.3x\n", 42);
  printf("   PRECI HEX INT   via %%.5x avec     42   : %#.5x\n", 42);
  printf("   PRECI HEX INT   via %%#.10x avec   42   : %#.10x\n", 42);

  // MELANGE de flags
  printf("\n   ---------- FT_PRINTF -----------\n");
  ft_printf("   FLAG 0    INT   via %%010d avec  42     : %010d\n", 42);
  ft_printf("   FLAG 0    INT   via %%010d avec  -42    : %010d\n", -42);
  ft_printf("   FLAG ' '  INT   via %% 4d avec   42     : % 4d\n", 42);
  ft_printf("   FLAG ' '  INT   via %% 4d avec   -42    : % 4d\n", -42);
  ft_printf("   FLAG +    INT   via %%+d avec    42     : %+d\n", 42);
  ft_printf("   FLAG - CHAR* via %%-10s avec 'Hello'    : %-10s\n", "Hello");
  ft_printf("   FLAG - INT via %%- 10d avec   42        : %- 10d\n", 42);
  ft_printf("   FLAG - INT via %%-10d avec   42         : %-10d\n", 42);

  printf("\n   ---------- PRINTF -----------\n");
  printf("   FLAG 0    INT   via %%010d avec  42     : %010d\n", 42);
  printf("   FLAG 0    INT   via %%010d avec  -42    : %010d\n", -42);
  printf("   FLAG ' '  INT   via %% 4d avec   42     : % 4d\n", 42);
  printf("   FLAG ' '  INT   via %% 4d avec   -42    : % 4d\n", -42);
  printf("   FLAG +    INT   via %%+d avec    42     : %+d\n", 42);
  printf("   FLAG - CHAR* via %%-10s avec 'Hello'    : %-10s\n", "Hello");
  printf("   FLAG - INT via %%- 10d avec   42        : %- 10d\n", 42);
  printf("   FLAG - INT via %%-10d avec   42         : %-10d\n", 42);



  printf("\n");
  return (0);
}

__attribute__((destructor))void destructeur()
{
	printf("destructor\n");
	while(1);
}
