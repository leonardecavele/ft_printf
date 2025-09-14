/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:38:50 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/14 13:51:44 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		(*s)++;
		f->pre = 0;
		if (**s && **s >= '0' && **s <= '9')
			f->pre = sm_atoii(s);
	}
	if (ft_strchr("cs%", **s))
		f->flags &= ~(FZR | FPL | FSP | FHS);
	if (ft_strchr("cspdiuxX%", **s))
	{
		va_copy(tmp, pm);
		f->v = value(**s, pm);
		f->n = szputpm(**s, tmp, -1, 2147483647);
		va_end(tmp);
	}
	return (n + format(**s, tmp, f));
}

int	ft_printf(const char *s, ...)
{
	va_list		pm;
	t_format	f;
	int			n;

	n = 0;
	va_start(pm, s);
	while (*s && n > -1)
	{
		f = (t_format){0};
		f.pre = -1;
		if (*s == '%')
		{
			s++;
			f.flags = flags((char **)&s);
			n += parse((char **)&s, pm, &f);
		}
		else
			n += write(1, s, 1);
		if (*s)
			s++;
	}
	va_end(pm);
	return (n);
}
