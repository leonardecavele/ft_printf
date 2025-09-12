/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:52:07 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/12 03:38:53 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	szputchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	szputstr(const char *s)
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

int	szputnbr(long long n)
{
	int		sz;
	char	c;

	sz = 0;
	if (n < 0)
	{
		szputchar('-');
		n = -n;
		sz++;
	}
	if (n > 9)
		sz += szputnbr(n / 10);
	c = n % 10 + '0';
	szputchar(c);
	return (sz + 1);
}

int	szputhex(unsigned long long n, char c, char a)
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
		return (szputchar('0'));
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
		sz += szputchar(b[i]);
	return (sz);
}
