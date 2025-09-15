/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:38:50 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/15 10:43:50 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	szputstr(const char *s)
{
	int	sz;

	if (!s)
		s = "(null)";
	sz = -1;
	while (s[++sz])
		;
	write(1, s, sz);
	return (sz);
}

static int	szputnbr(long long n)
{
	int		sz;
	char	c;

	sz = 0;
	if (n < 0)
	{
		sz += write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		sz += szputnbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
	return (sz + 1);
}

static int	szputhex(unsigned long long n, char a, char c)
{
	int		sz;
	char	b[16];
	int		d;
	int		i;

	sz = 0;
	i = 0;
	if (n == 0 && c == 'p')
		return (szputstr("(nil)"));
	if (n == 0)
		return (write(1, "0", 1));
	if (c == 'p')
		sz += szputstr("0x");
	while (n)
	{
		d = (unsigned int)(n & 0xF);
		if (d < 10)
			b[i++] = '0' + d;
		else
			b[i++] = a + (d - 10);
		n >>= 4;
	}
	while (i--)
		sz += write(1, &b[i], 1);
	return (sz);
}

static int	szputpm(va_list pm, char c)
{
	int	n;
	int	tmp;

	n = 0;
	if (c == 'c')
	{
		tmp = va_arg(pm, int);
		n += write(1, &tmp, 1);
	}
	else if (c == 's')
		n += szputstr(va_arg(pm, const char *));
	else if (c == 'p')
		n += szputhex((unsigned long long)va_arg(pm, void *), 'a', c);
	else if (c == 'd' || c == 'i')
		n += szputnbr((int)va_arg(pm, int));
	else if (c == 'u')
		n += szputnbr((unsigned int)va_arg(pm, unsigned int));
	else if (c == 'x')
		n += szputhex((unsigned long long)va_arg(pm, unsigned int), 'a', c);
	else if (c == 'X')
		n += szputhex((unsigned long long)va_arg(pm, unsigned int), 'A', c);
	else if (c == '%')
		n += write(1, "%", 1);
	return (n);
}

int	ft_printf(const char *s, ...)
{
	va_list	pm;
	int		n;

	n = 0;
	va_start(pm, s);
	while (*s && n > -1)
	{
		if (*s == '%')
		{
			s++;
			n += szputpm(pm, *s);
		}
		else
			n += write(1, s, 1);
		if (*s)
			s++;
	}
	va_end(pm);
	return (n);
}
