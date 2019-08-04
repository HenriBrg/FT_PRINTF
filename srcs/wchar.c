#include "../includes/ft_printf.h"

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

void wchar_to_str(t_printf *tab, wchar_t wc, int octets)
{
  tab->output = ft_strnew(octets + 1);

  if (octets == 1)
    tab->output = ft_memset(tab->output, wc, 1); // Caster (int)wc ?
  else if (octets == 2)
  {
    tab->output[0] = (wc >> 6) + 192;
  	tab->output[1] = ((wc & 63) + 128);
  }
  else if (octets == 3)
  {
    tab->output[0] = (wc >> 12) + 224;
  	tab->output[1] = ((wc >> 6) & 63) + 128;
  	tab->output[2] = ((wc & 63) + 128);
  }
  else if (octets == 4)
  {
    tab->output[0] = (wc >> 18) + 240;
  	tab->output[1] = ((wc >> 12) & 63) + 128;
  	tab->output[2] = ((wc >> 6) & 63) + 128;
  	tab->output[3] = ((wc & 63) + 128);
  }
  write(1, tab->output, octets);
}

void convertWCharTAndWString(t_printf *tab, char c)
{
  wchar_t wc;
  wchar_t *ws;

  if (c == 'C')
  {
    wc = va_arg(tab->args, wint_t);
    wchar_to_str(tab, wc, getSizeWchar(wc)); // Est ce que sizeof ne suffirai pas ?
  }
  else if (c == 'S')
    ws = va_arg(tab->args, wchar_t*);

}
