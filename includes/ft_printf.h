#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*

Approche possible pour gérer les types de variable tous en même temps
- Utiliser typeof()
- Compter la valeur ascci de chaque type : int = i + n + t = 105 + 110 + 116 => 331 => Type int
- Pouvoir récupérer dynamiquement un type de varable et le placer dans va_arg

*/

# include <locale.h> // Pour tester les symboles, etc ...
# include <stdarg.h>

# include "./libft.h"


/*
** i          : itération sur le string format
** outputSize : Taille à retrouner par printf
** args       : suite d'arguments passé à printf
** format     : 1er argument passé, qui est un string
** width      : Taille minimum du champ
** precision  : gère la précision
*/

typedef struct s_printf {

  va_list args;
  char    *format;

  int     i;
  int     returnSize;

  /*
  ** Pour gérer les flags -+0# et ' ' (espace)
  */
  int			minus;
	int			plus;
	int			space;
	int			zero;
	int			hash;

  /*
  ** Pour gérer les size/length (h, hh, l, ll, j, z)
  ** https://docs.microsoft.com/fr-fr/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions?view=vs-2019
  */
  int     h;
  int     hh;
  int     l;
  int     ll;
  int     j;
  int     z;

  int    width;
  int    precision;
}              t_printf;

void setConfig(t_printf *tab);
void showConfig(t_printf *tab);
void handleDisplay(t_printf *tab);

#endif
