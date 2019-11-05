/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:07:59 by hberger           #+#    #+#             */
/*   Updated: 2019/11/05 14:57:21 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** reset_config() intervient pour chaque conversion (c.a.d occurence de %)
*/

void	reset_config(t_printf *tab)
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

void	finish_precision(t_printf *tab, char *tmp, int size)
{
	char	*tmp2;

	tmp2 = ft_strjoin(tmp, tab->output + size);
	free(tab->output);
	tab->output = ft_strdup(tmp2);
	free(tmp2);
}

void	zero_precision_cut(t_printf *tab, char *strprefix)
{
	free(tab->output);
	if ((tab->output = ft_strjoin(strprefix, "")) || 1)
		return (free(strprefix));
}

void	except_case_preci(t_printf *tab, char *tmp, char *strprefix)
{
	free(tmp);
	tmp = ft_strjoin(strprefix, tab->output);
	tab->output = ft_strdup(tmp);
	free(tmp);
	free(strprefix);
}
