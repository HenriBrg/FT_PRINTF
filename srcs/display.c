/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:32:05 by hberger           #+#    #+#             */
/*   Updated: 2019/10/20 21:18:03 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** convert_int() intervient pour les conversion d'int signés
** intmax_toa_base gère tous les types de nombres signés
*/

static void		convert_int(t_printf *tab)
{
	intmax_t	n;

	n = 0;
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
** convert_unsigned_int() intervient pour toutes les conversion d'unsigned int
** uintmax_toa_base gère tous les types de nombres non signés
*/

static void		convert_unsigned_int(t_printf *tab, char c)
{
	uintmax_t	n;

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
		tab->output = ft_uintmaxt_toa_base("01234567", n);
	else if (c == 'u' || c == 'U')
		tab->output = ft_uintmaxt_toa_base("0123456789", n);
	else if (c == 'x')
		tab->output = ft_uintmaxt_toa_base("0123456789abcdef", n);
	else if (c == 'X')
		tab->output = ft_uintmaxt_toa_base("0123456789ABCDEF", n);
	else if (c == 'b')
		tab->output = ft_uintmaxt_toa_base("01", n);
}

/*
** convert_pointer() intervient pour la conversion %p
*/

static void		convert_pointer(t_printf *tab)
{
	char 		*tmp;
	uintmax_t	ptr;

	ptr = (unsigned long long int)va_arg(tab->args, void*);
	tmp = ft_uintmaxt_toa_base("0123456789abcdef", ptr);
	tab->output = ft_strjoin("0x", tmp);
	free(tmp);
}

/*
** convert_char_and_string() intervient pour les conversion %s et %c
** NB : la vraie fonction printf affiche (null) si la valeur de l'arg est nulle
**
** L'int arg gere le cas d'un %.2c
*/

static void		convert_char_and_string(t_printf *tab, char c)
{
	char	*tmp;
	int		arg;

	if (c == 'c')
	{
		arg = va_arg(tab->args, int);
		if (arg == 0 && (tab->stderr = 1))
			tab->output = ft_strdup("^@");
		else
			tab->output = ft_memset(ft_strnew(2), arg, 1);
	}
	else if (c == 's')
	{
		/*
		D'un % à un autre, tab->output est reinitialisé, mais pas free
		*/
		tmp = va_arg(tab->args, char*);
		if (tmp == 0)
			tab->output = ft_strdup("(null)");
		else
			tab->output = tmp;
	}
}

/*
** La fonction handleDisplay() gère le type et la size/length (4 & 5)
*/

void			handle_display(t_printf *tab, char c)
{
	if (c == 'i' || c == 'd' || c == 'D')
		convert_int(tab);
	else if (c == 'o' || c == 'u' || c == 'U' || c == 'x' || c == 'X'
											|| c == 'b' || c == 'O')
		convert_unsigned_int(tab, c);
	else if (c == 'p')
		convert_pointer(tab);
	else if (c == 's' || c == 'c')
		convert_char_and_string(tab, c);
	else if (c == '%')
		tab->output = ft_memset(ft_strnew(2), '%', 1);
}
