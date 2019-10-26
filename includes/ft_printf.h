/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:47:57 by hberger           #+#    #+#             */
/*   Updated: 2019/10/27 00:18:49 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

# include "../libft/libft.h"

typedef struct	s_printf {

	va_list		args;
	char		*format;
	char		*output;
	int			i;
	int			return_size;
	int			except;
	int			minus;
	int			plus;
	int			space;
	int			zero;
	int			hash;
	int			h;
	int			hh;
	int			l;
	int			ll;
	int			j;
	int			z;
	int			width;
	int			width_config;
	int			precision;
	int			precision_config;

}				t_printf;

int				ft_printf(const char *format, ...);
void			set_config(t_printf *tab);
void			handle_display(t_printf *tab, char c);
void			apply_config(t_printf *tab);
void			reset_config(t_printf *tab);

#endif
