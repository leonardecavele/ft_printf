/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:38:50 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/10 17:13:05 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_bonus.h"

static int64_t	vue(char c, va_list pm)
{
	int64_t	v;

	v = 0;
	if (ft_strchr("cdi", c))
		v = (int64_t)va_arg(pm, int);
	else if (c == 's')
		v = (int64_t)va_arg(pm, const char *);
	else if (c == 'p')
		v = (int64_t)va_arg(pm, void *);
	else if (ft_strchr("uxX", c))
		v = (int64_t)va_arg(pm, unsigned int);
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
		f->v = vue(**s, pm);
		f->n = szputpm_en(0, tmp, **s, INT_MAX);
		n += format(**s, tmp, f);
		va_end(tmp);
	}
	return (n);
}

static bool	error(t_printf *printf)
{
	printf->n += printf->cur;
	if (printf->cur > -1)
		return (0);
	printf->n = -1;
	return (1);
}

int	ft_printf(const char *s, ...)
{
	t_printf	printf;
	t_format	f;

	printf = (t_printf){0};
	va_start(printf.pm, s);
	while (*s)
	{
		f = (t_format){0};
		f.pre = -1;
		if (*s == '%')
		{
			s++;
			f.flags = flags((char **)&s);
			printf.cur = parse((char **)&s, printf.pm, &f);
		}
		else
			printf.cur = write(1, s, 1);
		if (error(&printf))
			break ;
		if (*s)
			s++;
	}
	va_end(printf.pm);
	return (printf.n);
}
