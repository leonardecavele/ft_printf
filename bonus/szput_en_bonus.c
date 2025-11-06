/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   szput_en_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:52:07 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/06 17:40:09 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_bonus.h"

static int	szputchar_en(char c, int en)
{
	if (en)
		return (write(1, &c, 1));
	else
		return (1);
}

static int	szputnstr_en(int en, const char *s, int n)
{
	int	sz;

	if (!s)
		return (szputnstr_en(en, "(null)", 6));
	sz = -1;
	while (s[++sz] && sz < n)
		;
	if (en)
		return (write(1, s, sz));
	else
		return (sz);
}

static int	szputnbr_en(int64_t n, int en)
{
	int		sz;
	char	c;

	sz = 0;
	if (n < 0)
		n = -n;
	if (n > 9)
		sz += szputnbr_en(n / 10, en);
	c = n % 10 + '0';
	return (sz + szputchar_en(c, en));
}

static int	szputhex_en(uint64_t n, char a, char c, int en)
{
	int		sz;
	char	b[16];
	int		d;
	int		i;

	sz = 0;
	i = 0;
	if (c == 'p' && n == 0)
		return (szputnstr_en(en, "(nil)", 5));
	if (n == 0)
		return (szputchar_en('0', en));
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
		sz += szputchar_en(b[i], en);
	return (sz);
}

int	szputpm_en(int en, va_list pm, char c, int n)
{
	va_list	tmp;
	int		sz;

	va_copy(tmp, pm);
	sz = 0;
	if (c == 'c')
		sz += szputchar_en(va_arg(tmp, int), en);
	else if (c == 's')
		sz += szputnstr_en(en, va_arg(tmp, const char *), n);
	else if (c == 'p')
		sz += szputhex_en((uint64_t)va_arg(tmp, void *), 'a', c, en);
	else if (c == 'd' || c == 'i')
		sz += szputnbr_en((int)va_arg(tmp, int), en);
	else if (c == 'u')
		sz += szputnbr_en((unsigned int)va_arg(tmp, unsigned int), en);
	else if (c == 'x')
		sz += szputhex_en((uint64_t)va_arg(tmp, unsigned int), 'a', c, en);
	else if (c == 'X')
		sz += szputhex_en((uint64_t)va_arg(tmp, unsigned int), 'A', c, en);
	else if (c == '%')
		sz += szputchar_en('%', en);
	va_end(tmp);
	return (sz);
}
