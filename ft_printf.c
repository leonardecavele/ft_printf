/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:38:50 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/13 01:02:37 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

t_ll	get_value(char c, va_list pm)
{
	va_list cp;
	t_ll	v;

	va_copy(cp, pm);
	v = 0;
	if (c == 'c' || c == 'd' || c == 'i')
		v = (t_ll)va_arg(cp, int);
	else if (c == 's')
		v = (t_ll)va_arg(cp, const char *);
	else if (c == 'p')
		v = (t_ll)va_arg(cp, void *);
	else if (c == 'u' || c == 'x' || c == 'X')
		v = (t_ll)va_arg(cp, unsigned int);
	va_end(cp);
	return (v);
}

static int	handle_flag(char c, va_list pm, t_flags *f)
{
	t_ll	v;
	int		n;

	n = 0;
	if (c == 'c' || c == 's' || c == '%')
		f->f &= ~(Z_F | P_F | S_F | H_F);
	v = get_value(c, pm);
	if ((c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X') && !f->p && !v)
		f->n = 0;
	if (c == 's' && f->p > -1)
		f->n = f->p;
	if (c == 'p' && !v)
		return (write(1, "(nil)", 5));
	if ((c == 'd' || c == 'i') && (f->f & P_F || f->f & S_F || v < 0))
		n += 1;
	if ((c == 'x' || c == 'X') && (f->f & H_F) && v)
		n += 2;
	if (c == 'p' && v && !(f->w > 0 && !(f->f & M_F) && !(f->f & Z_F)))
		n += szputnstr("0x", 1, 2);
	else if (c == 'p' && v)
		n += 2;
	if (f->p > -1)
		f->z = max(0, f->p - f->n); 
	f->d = max(0, f->w - (n + f->z + f->n));
	if (!(f->f & M_F) && (f->p > -1 || !(f->f & Z_F)))
		while (f->d--)
			n += szputchar(' ', 1);
	if (c == 'p' && v && f->w > 0 && !(f->f & M_F) && !(f->f & Z_F))
		n += szputnstr("0x", 1, 2);
	if ((c == 'd' || c == 'i') && v < 0)
		szputchar('-', 1);
	else if ((c == 'd' || c == 'i') && f->f & P_F)
		szputchar('+', 1);
	else if ((c == 'd' || c == 'i') && f->f & S_F)
		szputchar(' ', 1);
	if ((c == 'x') && f->f & H_F && v)
		write(1, "0x", 2);
	else if ((c == 'X') && f->f & H_F && v)
		write(1, "0X", 2);
	if (!(f->f & M_F) && f->f & Z_F && f->p < 0)
		while (f->d-- && c != 'c')
			n += szputchar('0', 1);
	else
		while (f->z-- && c != 'c')
			n += szputchar('0', 1);
	if (!(!f->p && !v))
		n += szputpm(c, pm, 1, f->n);
	if (f->f & M_F)
		while (f->d--)
			n += szputchar(' ', 1);
	return (n);
}

static short	get_flag(char **s)
{
	short	f;

	f = 0;
	while (**s && (**s == '-' || **s == '0' || **s == '#'
			|| **s == '+' || **s == ' '))
	{
		if (**s == '-')
			f |= M_F;
		else if (**s == '0')
			f |= Z_F;
		else if (**s == '#')
			f |= H_F;
		else if (**s == '+')
			f |= P_F;
		else if (**s == ' ')
			f |= S_F;
		(*s)++;
	}
	if (f & M_F)
		f &= ~Z_F;
	if (f & P_F)
		f &= ~S_F;
	return (f);
}

static int	parse(char **s, va_list pm, t_flags *f)
{
	int		n;

	n = 0;
	f->f = get_flag(s);
	if (**s && **s >= '0' && **s <= '9')
		f->w = sm_atoii(s);
	if (**s && **s == '.')
	{
		(*s)++;
		f->p = 0;
		if (**s && **s >= '0' && **s <= '9')
			f->p = sm_atoii(s);
	}
	if (**s == 'c' || **s == 's' || **s == 'p' || **s == 'd' || **s == 'i'
		|| **s == 'u' || **s == 'x' || **s == 'X' || **s == '%')
	{
		f->n = szputpm(**s, pm, -1, 2147483647);
		n += handle_flag(**s, pm, f);
	}
	else
		return (-1);
	return (n);
}

int	ft_printf(const char *s, ...)
{
	va_list	pm;
	t_flags	f;
	int		n;

	n = 0;
	va_start(pm, s);
	while (*s && n > -1)
	{
		f.f = 0;
		f.w = 0;
		f.p = -1;
		f.z = 0;
		f.n = 0;
		if (*s == '%')
		{
			s++;
			n += parse((char **)&s, pm, &f); //problem here
		}
		else
			n += write(1, s, 1);
		if (*s)
			s++;
	}
	va_end(pm);
	return (n);
}
