#include "../includes/ft_printf.h"

/*
** RAS
*/

static void convert_int(t_printf *tab)
{
  intmax_t n;

  if (tab->h)
    n = (short)va_arg(tab->args, int);
  else if (tab->hh)
    n = (char)va_arg(tab->args, int);
  else if (tab->l)
    n = va_arg(tab->args, long);
  else if (tab->ll)
    n = va_arg(tab->args, long long);
  else if (tab->j)
    n = va_arg(tab->args, intmax_t);
  else if (tab->z)
    n = va_arg(tab->args, ssize_t);
  else
    n = va_arg(tab->args, int);
  tab->output = ft_intmaxt_toa_base("0123456789", n);
}

/*
** RAS
*/

static void convert_unsigned_int(t_printf *tab, char c)
{
  uintmax_t n;

  if (tab->h)
    n = (unsigned short)va_arg(tab->args, unsigned int);
  else if (tab->hh)
    n = (unsigned char)va_arg(tab->args, unsigned int);
  else if (tab->l)
    n = va_arg(tab->args, unsigned long);
  else if (tab->ll)
    n = va_arg(tab->args, unsigned long long);
  else if (tab->j)
    n = va_arg(tab->args, uintmax_t);
  else if (tab->z)
    n = va_arg(tab->args, size_t);
  else
    n = va_arg(tab->args, unsigned int);
  if (c == 'o' || c == 'O')
    tab->output = ft_Uintmaxt_toa_base("01234567", n);
  else if (c == 'u' || c == 'U')
    tab->output = ft_Uintmaxt_toa_base("0123456789", n);
  else if (c == 'x')
    tab->output = ft_Uintmaxt_toa_base("0123456789abcdef", n);
  else if (c == 'X')
    tab->output = ft_Uintmaxt_toa_base("0123456789ABCDEF", n);
  else if (c == 'b')
    tab->output = ft_Uintmaxt_toa_base("01", n);
}

/*
** RAS
*/

static void convert_pointer(t_printf *tab)
{
  uintmax_t ptr;

  ptr = (unsigned long long int)va_arg(tab->args, void*);
  tab->output = ft_strjoin("0x", ft_Uintmaxt_toa_base("0123456789abcdef", ptr));
}

/*
** RAS
*/

static void convert_char_and_string(t_printf *tab, char c)
{
  if (c == 'c')
    tab->output = ft_memset(ft_strnew(2), va_arg(tab->args, int), 1);
  else if (c == 's')
    tab->output = va_arg(tab->args, char*);
}

/*
** La fonction handleDisplay() gère le type et la size/length (4 & 5)
**
** hh	Convert a variable of type char to integer and print
** h	Convert a variable of type short to integer and print
** l	For integers, a variable of type long is expected
** ll	For integers, a variable of type long long is expected
** L	For floating point, a variable of type long double is expected
** z	For integers, an argument is expected of type size_t
** j  For integers, an argument is expected of type intmax_t
*/

void  handle_display(t_printf *tab, char c)
{
  if (c == 'i' || c == 'd' || c == 'D')
    convert_int(tab);
  else if (c == 'o' || c == 'u' || c == 'U' || c == 'x' || c == 'X' || c == 'b')
    convert_unsigned_int(tab, c);
  else if (c == 'p')
    convert_pointer(tab);
  else if (c == 's' || c == 'c')
    convert_char_and_string(tab, c);
  else if (c == 'S' || c == 'C')
    convert_wchart_and_wstring(tab, c);
  else if (c == '%')
    tab->output = ft_memset(ft_strnew(2), '%', 1);
}
