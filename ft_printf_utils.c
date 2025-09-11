/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:52:07 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/11 22:10:01 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	szputchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	szputstr(char *s)
{
	int	sz;

	if (!s)
		return (0);
	sz = -1;
	while (s[++sz])
		;
	write(1, s, sz);
	return (sz);
}

int	szputnbr(int n)
{
	long	nb;
	int		sz;
	char	c;

	nb = n;
	sz = 0;
	if (nb < 0)
	{
		szputchar('-');
		nb = -nb;
		sz++;
	}
	if (nb > 9)
		sz += szputnbr(nb / 10);
	c = nb % 10 + '0';
	szputchar(c);
	return (sz + 1);
}
