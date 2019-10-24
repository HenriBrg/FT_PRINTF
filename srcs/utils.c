/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:07:59 by hberger           #+#    #+#             */
/*   Updated: 2019/10/24 18:16:19 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** reset_config() intervient pour chaque conversion (c.a.d occurence de %)
**
**
** if (tab->output)
** {
** // POURQUOI CA AFFICHE NIMPORTEQUOI AU PREMIER APPEL ? ^Y^Q^]M-^R��^]$
** 	printf("----------->%s\n", tab->output);
** 	//free(tab->output);
** }
** Impossible de free tab->output ici, why ?
*/

void		reset_config(t_printf *tab)
{
	tab->output = 0;
	tab->except = 0;
	tab->minus = 0;
	tab->plus = 0;
	tab->space = 0;
	tab->zero = 0;
	tab->hash = 0;
	tab->h = 0;
	tab->hh = 0;
	tab->l = 0;
	tab->ll = 0;
	tab->j = 0;
	tab->z = 0;
	tab->width = 0;
	tab->precision = 0;
	tab->width_config = 0;
	tab->precision_config = 0;
}
