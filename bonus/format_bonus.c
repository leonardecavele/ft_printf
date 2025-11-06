/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:03:39 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/06 14:18:15 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_bonus.h"

static int	prefix(char c, t_format *f)
{
	int	n;

	n = 0;
	if (ft_strchr("di", c) && f->v < 0)
		n += write(1, "-", 1);
	else if (ft_strchr("di", c) && f->flags & FPL)
		n += write(1, "+", 1);
	else if (ft_strchr("di", c) && f->flags & FSP)
		n += write(1, " ", 1);
	if (((c == 'x' && f->flags & FHS) || c == 'p') && f->v)
		n += write(1, "0x", 2);
	else if (c == 'X' && f->flags & FHS && f->v)
		n += write(1, "0X", 2);
	return (n);
}

static int	zer(t_format *f)
{
	int	n;

	n = 0;
	if (!(f->flags & FMN) && f->flags & FZR && f->pre < 0)
		while (f->pad--)
			n += write(1, "0", 1);
	else
		while (f->zer--)
			n += write(1, "0", 1);
	return (n);
}

static int	lpad(char c, t_format *f)
{
	int	n;

	n = 0;
	if (f->pre > -1 && f->pre < 6 && c == 's' && f->v == 0)
	{
		while (f->wid--)
			n += write(1, " ", 1);
		f->pad = 0;
	}
	if (!(f->flags & FMN) && (f->pre > -1 || !(f->flags & FZR)) && c != '%')
		while (f->pad--)
			n += write(1, " ", 1);
	return (n);
}

static int	rpad(char c, t_format *f)
{
	int	n;

	n = 0;
	if (f->flags & FMN && c != '%')
		while (f->pad--)
			n += write(1, " ", 1);
	return (n);
}

int	format(char c, va_list pm, t_format *f)
{
	int	n;
	int	pre;

	if (f->v == 0 && f->pre == 0 && ft_strchr("diuxX", c))
		f->n = 0;
	if (c == 's' && f->pre > -1)
		f->n = min(f->n, f->pre);
	pre = 0;
	if (ft_strchr("di", c) && (f->flags & FPL || f->flags & FSP || f->v < 0))
		pre = 1;
	if ((ft_strchr("xX", c) && (f->flags & FHS) && f->v) || (c == 'p' && f->v))
		pre = 2;
	if (f->pre > -1 && ft_strchr("diuxX", c))
		f->zer = max(0, f->pre - f->n);
	f->pad = max(0, f->wid - (pre + f->zer + f->n));
	n = 0;
	n += lpad(c, f);
	if (c == 's' && f->pre > -1 && f->pre < 6 && f->v == 0)
		return (n);
	n += prefix(c, f);
	n += zer(f);
	if (!(ft_strchr("diuxX", c) && f->pre == 0 && f->v == 0))
		n += szputpm_en(1, pm, c, f->n);
	n += rpad(c, f);
	return (n);
}
