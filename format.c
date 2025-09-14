/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:03:39 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/14 12:26:30 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	prefix(char c, t_format *f)
{
	if (ft_strchr("di", c) && f->v < 0)
		szputchar('-', 1);
	else if (ft_strchr("di", c) && f->flags & FPL)
		szputchar('+', 1);
	else if (ft_strchr("di", c) && f->flags & FSP)
		szputchar(' ', 1);
	if (((c == 'x' && f->flags & FHS) || c == 'p') && f->v)
		szputnstr("0x", 1, 2);
	else if (c == 'X' && f->flags & FHS && f->v)
		szputnstr("0X", 1, 2);
}

static int	zer(t_format *f)
{
	int	n;

	n = 0;
	if (!(f->flags & FMN) && f->flags & FZR && f->pre < 0)
		while (f->pad--)
			n += szputchar('0', 1);
	else
		while (f->zer--)
			n += szputchar('0', 1);
	return (n);
}

static int	lpad(t_format *f)
{
	int	n;
	
	n = 0;
	if (!(f->flags & FMN) && (f->pre > -1 || !(f->flags & FZR)))
		while (f->pad--)
			n += szputchar(' ', 1);
	return (n);
}

static int	rpad(t_format *f)
{
	int	n;

	n = 0;
	if (f->flags & FMN)
		while (f->pad--)
			n += szputchar(' ', 1);
	return (n);
}

int	format(char c, va_list pm, t_format *f)
{
	int		n;

	n = 0;
	if (ft_strchr("di", c) && (f->flags & FPL || f->flags & FSP || f->v < 0))
		n += 1;
	if (ft_strchr("xX", c) && (f->flags & FHS) && f->v)
		n += 2;
	if (c == 'p' && f->v)
		n += 2;
	if (f->pre > -1 && ft_strchr("diuxX", c))
		f->zer = max(0, f->pre - f->n);
	f->pad = max(0, f->wid - (n + f->zer + f->n));
	n += lpad(f);
	prefix(c, f);
	n += zer(f);
	if (!(ft_strchr("diuxX", c) && f->pre == 0 && f->v == 0))
		n += szputpm(c, pm, 1, f->n);
	n += rpad(f);
	return (n);
}
