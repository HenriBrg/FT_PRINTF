#include "../includes/ft_printf.h"

/*
** Voir les paliers sur : https://fr.wikipedia.org/wiki/UTF-8
** La fonction getSizeWchar retourne la taille en bytes/octets du wchar_t donné
*/

int getSizeWchar(wchar_t wc)
{
  if (wc <= 127)
		return (1);
	else if (wc >= 127 && wc <= 2047)
		return (2);
	else if (wc >= 2048 && wc <= 65535)
		return (3);
	else
		return (4);
}
/*
** wchar_to_str() converti un wchar de taille octets (1 si ascii < 127, 2, 3 voire 4)
** en un string de taille octets + 1 (pour le '\0')
** La structure des bitwise a été récupéré sur le web, donc TODO : capter ce qu'ils font
*/

char *wchar_to_str(wchar_t wc, int octets)
{
  char *str;

  str = ft_strnew(octets + 1);
  if (octets == 1)
    str = ft_memset(str, wc, 1);
  else if (octets == 2)
  {
    str[0] = (wc >> 6) + 192;
  	str[1] = ((wc & 63) + 128);
  }
  else if (octets == 3)
  {
    str[0] = (wc >> 12) + 224;
  	str[1] = ((wc >> 6) & 63) + 128;
  	str[2] = ((wc & 63) + 128);
  }
  else if (octets == 4)
  {
    str[0] = (wc >> 18) + 240;
  	str[1] = ((wc >> 12) & 63) + 128;
  	str[2] = ((wc >> 6) & 63) + 128;
  	str[3] = ((wc & 63) + 128);
  }
  return (str);
}


/*
** La fonction wcstrlen() retourne la size d'un string de wchar_t
** On test chaque char et si l'un renvoie \0, c'est que c'est la fin
** Mais ce \O peut semblerai-t-il être placé sur l'octet 1, 2, voire 3 d'un wchar_t
*/

size_t wcstrlen(const wchar_t *s)
{
  size_t i;

  i = 0;
  while (s[i] != L'\0')
   {
      if (s[++i] == L'\0')
        return i;
      if (s[++i] == L'\0')
        return i;
      if (s[++i] == L'\0')
        return i;
      ++i;
   }
  return (i);
}

/*
**  strwchar_to_str() est la clé de voute pour le %S de printf
** 1 - On détermine la taille de la chaine de wchar_t avec wcstrlen() (code source de la fonction système wcslen)
** 2 - On alloue str avec la taille nécessaire pour accueilir chaque wchar_t
**     Exemple :  'a' en wchar_t possède une size de 1 (bytes ?) obtenue via getSizeWchar()
                  '' en wchar_t possède une size de 3 (bytes ?)
                  'b' en wchar_t possède une size de 1 (bytes ?)
                  '𝄞' en wchar_t possède une size de 4 (bytes ?)

                  Au total on a besoin d'un chaine de taille (1 + 3 + 1 + 4) + 1
** 3 - On appel wchar_to_str() sur chaque wchar_t de la chaine de wchar_t
       qui retourne un string (de char) sur lequel on appel strjoin
*/


char *strwchar_to_str(wchar_t *strwc)
{
  size_t i;
  size_t size_wc;
  size_t alloc_size_str;
  char *str;

  i = -1;
  alloc_size_str = 0;
  size_wc = wcstrlen(strwc);
  while (++i < size_wc)
    alloc_size_str += getSizeWchar(strwc[i]);
  if ((str = malloc(sizeof(char) * (alloc_size_str + 1))) == 0)
    return (0);
  str[0] = '\0';
  i = -1;
  while (++i < size_wc)
    str = ft_strjoin(str, wchar_to_str(strwc[i], getSizeWchar(strwc[i])));
  return (str);
}

/*
** convertWCharTAndWString gère les cas de wchar_t %C et %S
** %S consiste en un appel en boucle des fonctions utilisée pour %C
*/

void convert_wchart_and_wstring(t_printf *tab, char c)
{
  wchar_t wc;
  wchar_t *ws;

  if (c == 'C')
  {
    wc = va_arg(tab->args, wint_t);
    tab->output = wchar_to_str(wc, getSizeWchar(wc)); // Est ce que sizeof ne suffirai pas ?
  }
  else if (c == 'S')
  {
    ws = va_arg(tab->args, wchar_t*);
    tab->output = strwchar_to_str(ws);
  }
}
