/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   szput_fd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:52:07 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/15 10:27:56 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	szputchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

static int	szputnstr_fd(int fd, const char *s, int n)
{
	int	sz;

	if (!s)
		return (szputnstr_fd(fd, "(null)", 6));
	sz = -1;
	while (s[++sz] && sz < n)
		;
	write(fd, s, sz);
	return (sz);
}

static int	szputnbr_fd(t_ll n, int fd)
{
	int		sz;
	char	c;

	sz = 0;
	if (n < 0)
		n = -n;
	if (n > 9)
		sz += szputnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	szputchar_fd(c, fd);
	return (sz + 1);
}

static int	szputhex_fd(t_ull n, char a, char c, int fd)
{
	int		sz;
	char	b[16];
	int		d;
	int		i;

	sz = 0;
	i = 0;
	if (c == 'p' && n == 0)
		return (szputnstr_fd(fd, "(nil)", 5));
	if (n == 0)
		return (szputchar_fd('0', fd));
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
		sz += szputchar_fd(b[i], fd);
	return (sz);
}

int	szputpm_fd(int fd, va_list pm, char c, int n)
{
	va_list	tmp;
	int		sz;

	va_copy(tmp, pm);
	sz = 0;
	if (c == 'c')
		sz += szputchar_fd(va_arg(tmp, int), fd);
	else if (c == 's')
		sz += szputnstr_fd(fd, va_arg(tmp, const char *), n);
	else if (c == 'p')
		sz += szputhex_fd((t_ull)va_arg(tmp, void *), 'a', c, fd);
	else if (c == 'd' || c == 'i')
		sz += szputnbr_fd((int)va_arg(tmp, int), fd);
	else if (c == 'u')
		sz += szputnbr_fd((unsigned int)va_arg(tmp, unsigned int), fd);
	else if (c == 'x')
		sz += szputhex_fd((t_ull)va_arg(tmp, unsigned int), 'a', c, fd);
	else if (c == 'X')
		sz += szputhex_fd((t_ull)va_arg(tmp, unsigned int), 'A', c, fd);
	else if (c == '%')
		sz += szputchar_fd('%', fd);
	va_end(tmp);
	return (sz);
}
