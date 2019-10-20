/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 18:22:34 by hberger           #+#    #+#             */
/*   Updated: 2019/10/20 21:15:04 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** La fonction prefix n'intervient que si
** 1 : Il y a une width et le flag '0' est présent
** 2 : Il y a une précision
** S'il y a une width sans flag '0', il n'y a pas besoin de mettre de prefixe
** au début
** Préfixes possibles : - + 0 0x 0X et ' ' et uniquement sur les nombres
*/

char	*prefix(t_printf *tab, char c)
{
	int		size;
	char	*prefix;

	size = ft_strlen(tab->output);
	if (ft_strchr("dDioOuUxX", c) == NULL)
		return (0);
	if (size >= 1 && tab->output[0] == '-')
		prefix = ft_strdup("-");
	else if (size >= 1 && tab->output[0] == '+')
		prefix = ft_strdup("+");
	else if (size >= 1 && tab->output[0] == ' ')
		prefix = ft_strdup(" ");
	else if (tab->hash && size >= 1 && (c == 'o' || c == 'O') &&
									tab->output[0] == '0')
		prefix = ft_strdup("0");
	else if (tab->hash && size >= 2 && tab->output[0] == '0' &&
									tab->output[1] == 'x')
		prefix = ft_strdup("0x");
	else if (tab->hash && size >= 2 && tab->output[0] == '0' &&
									tab->output[1] == 'X')
		prefix = ft_strdup("0X");
	else
		prefix = NULL;
	return (prefix);
}

/*
** Alors ici c'est un peu compliqué (en partie à cause des 25 lignes maximum)
**
** apply_precision intervient (avant apply_width) si tab->precisionConfig = 1
** ft_strlen(strprefix) dans un if car sinon on segfault si strprefix = 0
** Si la precision vaut 0 et que l'argument va_arg = 0, c'est un cas unique
** dans lequel on renvoie l'éventuel prefixe (0, 0x, 0X, +, ...)
**
** Autre cas unique (if (strprefix != 0 && ...), si il y a un prefixe et qu'on
** est dans un conversion %#o
** alors le 0 de prefixe octal est considéré commme un 0 remplissant
** (au sens des 0 que la précision remplit)
**
** S'il y a un prefixe (ex : 0x), il est stocké dans strprefix
** La précision ne prend pas en compte le préfixe : exemple :
** PRECI HEX INT   via %.5x avec     42   : 0x0002a
** (on a 0002a de taille 5 = précision) puis le préfix
**
** Si on a un string, tab->precision caractère sont copiés et
** il peut donc y avoir un troncation
** A la différence de la width, la précision limite le nombre de chiffres
** sortant (une sorte d'arrondi), et non le nombre total de caractère
** (ce qui fait que l'éventuel préfixe est exclu)
*/

void	apply_precision(t_printf *tab, char c)
{
	int		i;
	int		size;
	int		prefix_size;
	char	*tmp;
	char	*strprefix;

	if (ft_strchr("dDioOuUxX", c) && tab->precisionConfig)
	{
		strprefix = prefix(tab, c);
		prefix_size = (strprefix != 0) ? ft_strlen(strprefix) : 0;
		if ((i = -1) && tab->precision == 0 &&
			ft_atoi(tab->output + prefix_size) == 0)
		{
			tab->output = ft_strjoin(strprefix, ft_strnew(1));
			return ;
		}
		size = ft_strlen(tab->output);
		tmp = ft_strnew(size + (tab->precision - size));
		while (++i < tab->precision - size + prefix_size)
			tmp[i] = '0';
		size = (strprefix != 0) ? ft_strlen(strprefix) : 0;
		tab->output = ft_strjoin(tmp, tab->output + size);
		if (strprefix != 0 && !(c == 'o' && tab->output[0] == '0'))
			tab->output = ft_strjoin(strprefix, tab->output);
		free(tmp);
	}
	else if (c == 's' && tab->precisionConfig == 1)
		tab->output = ft_strndup(tab->output, tab->precision);
}

/*
** apply_width intervient sur les nombres et string SI leur taille est inférieur
** à la width donnée
** Elle détermine la taille maximale de l'output (au sens de strlen(output)) et
** prend donc en compte la taille de l'éventuel du préfixe
** (à l'inverse de la précision).
**
** Si le flag 0 est activé, le remplissage se fera par des 0 et non des ' '
**
** Si l'output est nul, pour x raisons (par exemple, apply_precision() aura
** assigné tab->output à ft_strjoin(strprefix, ft_strnew(1)) qui peut parfois
** être nul, ou encore si va_arg retourne 0), on rempli simplement tab->output
** de 0 ou de ' ' selon la width
*/

void	apply_width(t_printf *tab)
{
	int		i;
	int		size;
	char	c;
	char	*tmp;
	char	*strprefix;

	c = (tab->zero == 1) ? '0' : ' ';
	strprefix = (tab->zero == 1) ? prefix(tab, tab->format[tab->i]) : 0;
	if (tab->output == 0)
		tab->output = ft_memset(ft_strnew(tab->width), c, tab->width);
	else if (tab->width > (int)ft_strlen(tab->output))
	{
		size = ft_strlen(tab->output);
		tmp = ft_strnew(size + (tab->width - size));
		i = -1;
		while (++i < tab->width - size)
			tmp[i] = c;
		if (strprefix != 0)
			tmp = ft_strjoin(strprefix, tmp);
		size = (strprefix != 0) ? ft_strlen(strprefix) : 0;
		tab->output = ft_strjoin(tmp, tab->output + size);
		free(tmp);
	}
}

/*
** Les flags + ' ' # sont gérés dans apply_flags
** (Le flag '-' sera géreé tout à la fin et le flag '0' sera géré dans width())
** Faille potentielle ligne 124 (if tab->hash) si il y a un prefix + ou ' '
** avant le '0' recherché
*/

void	apply_flags(t_printf *tab, char c)
{
	char *tmp;

	tmp = NULL;
	if (tab->plus && ft_strchr("idD", c) && !ft_strchr(tab->output, '-'))
		tmp = ft_strjoin("+", tab->output);
	else if (tab->space && ft_strchr("idD", c) && !ft_strchr(tab->output, '-'))
		tmp = ft_strjoin(" ", tab->output);
	else if (tab->hash && ft_strchr("xXoO", c) && tab->output[0] != '0')
	{
		if (c == 'o' || c == 'O')
			tmp = ft_strjoin("0", tab->output);
		else if (c == 'x')
			tmp = ft_strjoin("0x", tab->output);
		else if (c == 'X')
			tmp = ft_strjoin("0X", tab->output);
	}
	if (tmp)
	{
		free(tab->output);
		tab->output = ft_strdup(tmp);
		free(tmp);
	}
}

/*
** Ordre d'application de la config :
** 1/ Flags + (ajoute + ou -), flag ' ' (ajoute +) et flag # (ajoute 0, 0x, 0X)
** 2/ Width (width combiné ou non au flag 0) OU Précision
** (qui par défaut remplit par 0)
** 3/ Gestion du flag '-' et gestion de l'exception avec flag '-' et flag ' '
** sur un int positif (qui aura un prefixe ' ')
*/

void	apply_config(t_printf *tab)
{
	int		i;
	int		place;
	int		minplus;
	char	*tmp;

	apply_flags(tab, tab->format[tab->i]);
	if (tab->precisionConfig && ft_strchr("dDiOouUxXsc", tab->format[tab->i]))
		apply_precision(tab, tab->format[tab->i]);
	if (tab->widthConfig == 1)
		apply_width(tab);
	if (tab->minus)
	{
		i = -1;
		place = 0;
		minplus = 0;
		if (tab->space && ft_strchr("idD", tab->format[tab->i])
			&& !ft_strchr(tab->output, '-'))
			minplus = 1;
		while (tab->output[++i] == ' ')
			place++;
		tmp = ft_memset(ft_strnew(place + 1), ' ', place);
		tab->output = ft_strjoin(tab->output + place - minplus, tmp + minplus);
		free(tmp);
	}
}
