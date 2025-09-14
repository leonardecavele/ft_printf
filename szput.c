/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   szput.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:52:07 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/14 13:55:12 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	szputchar(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

static int	szputnstr(const char *s, int fd, int n)
{
	int	sz;

	if (!s)
		return (szputnstr("(null)", fd, 6));
	sz = -1;
	while (s[++sz] && sz < n)
		;
	write(fd, s, sz);
	return (sz);
}

static int	szputnbr(t_ll n, int fd)
{
	int		sz;
	char	c;

	sz = 0;
	if (n < 0)
		n = -n;
	if (n > 9)
		sz += szputnbr(n / 10, fd);
	c = n % 10 + '0';
	szputchar(c, fd);
	return (sz + 1);
}

static int	szputhex(t_ull n, char a, int fd, char c)
{
	int		sz;
	char	b[16];
	int		d;
	int		i;

	sz = 0;
	i = 0;
	if (c == 'p' && n == 0)
		return (szputnstr("(nil)", fd, 5));
	if (n == 0)
		return (szputchar('0', fd));
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
		sz += szputchar(b[i], fd);
	return (sz);
}

int	szputpm(char c, va_list pm, int fd, int n)
{
	va_list	tmp;
	int		sz;

	va_copy(tmp, pm);
	sz = 0;
	if (c == 'c')
		sz += szputchar(va_arg(tmp, int), fd);
	else if (c == 's')
		sz += szputnstr(va_arg(tmp, const char *), fd, n);
	else if (c == 'p')
		sz += szputhex((t_ull)va_arg(tmp, void *), 'a', fd, c);
	else if (c == 'd' || c == 'i')
		sz += szputnbr((int)va_arg(tmp, int), fd);
	else if (c == 'u')
		sz += szputnbr((unsigned int)va_arg(tmp, unsigned int), fd);
	else if (c == 'x')
		sz += szputhex((t_ull)va_arg(tmp, unsigned int), 'a', fd, c);
	else if (c == 'X')
		sz += szputhex((t_ull)va_arg(tmp, unsigned int), 'A', fd, c);
	else if (c == '%')
		sz += szputchar('%', fd);
	va_end(tmp);
	return (sz);
}
