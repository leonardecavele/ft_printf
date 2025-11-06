/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:38:50 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/06 14:26:18 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_bonus.h"

static t_ll	value(char c, va_list pm)
{
	t_ll	v;

	v = 0;
	if (ft_strchr("cdi", c))
		v = (t_ll)va_arg(pm, int);
	else if (c == 's')
		v = (t_ll)va_arg(pm, const char *);
	else if (c == 'p')
		v = (t_ll)va_arg(pm, void *);
	else if (ft_strchr("uxX", c))
		v = (t_ll)va_arg(pm, unsigned int);
	return (v);
}

static short	flags(char **s)
{
	short	f;

	f = 0;
	while (**s && ft_strchr("-0#+ ", **s))
	{
		if (**s == '-')
			f |= FMN;
		else if (**s == '0')
			f |= FZR;
		else if (**s == '#')
			f |= FHS;
		else if (**s == '+')
			f |= FPL;
		else if (**s == ' ')
			f |= FSP;
		(*s)++;
	}
	if (f & FMN)
		f &= ~FZR;
	if (f & FPL)
		f &= ~FSP;
	return (f);
}

static int	parse(char **s, va_list pm, t_format *f)
{
	va_list	tmp;
	int		n;

	n = 0;
	if (**s && **s >= '0' && **s <= '9')
		f->wid = sm_atoii(s);
	if (**s && **s == '.')
	{
		f->pre = 0;
		if (*++(*s) && **s >= '0' && **s <= '9')
			f->pre = sm_atoii(s);
	}
	if (ft_strchr("cs%", **s))
		f->flags &= ~(FZR | FPL | FSP | FHS);
	if (ft_strchr("cspdiuxX%", **s))
	{
		va_copy(tmp, pm);
		f->v = value(**s, pm);
		f->n = szputpm_en(0, tmp, **s, 2147483647);
		n += format(**s, tmp, f);
		va_end(tmp);
	}
	return (n);
}

int	ft_printf(const char *s, ...)
{
	va_list		pm;
	t_format	f;
	int			n;
	int			n_ccl;

	n = 0;
	n_ccl = 0;
	va_start(pm, s);
	while (*s && n > -1)
	{
		f = (t_format){0};
		f.pre = -1;
		if (*s == '%')
		{
			s++;
			f.flags = flags((char **)&s);
			n_ccl = parse((char **)&s, pm, &f);
		}
		else
			n_ccl = write(1, s, 1);
		if (n_ccl > -1)
			n += n_ccl;
		else
			return (-1);
		if (*s)
			s++;
	}
	va_end(pm);
	return (n);
}
