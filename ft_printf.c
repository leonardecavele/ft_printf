/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:38:50 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/14 00:03:47 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

static int	handle_arg(const char *s, va_list pm)
{
	int	n;

	n = 0;
	if (*s == 'c')
		n += szputchar(va_arg(pm, int));
	else if (*s == 's')
		n += szputstr(va_arg(pm, const char *));
	else if (*s == 'p')
		n += szputhex((unsigned long long)va_arg(pm, void *), *s, 'a');
	else if (*s == 'd' || *s == 'i')
		n += szputnbr((int)va_arg(pm, int));
	else if (*s == 'u')
		n += szputnbr((unsigned int)va_arg(pm, unsigned int));
	else if (*s == 'x')
		n += szputhex((unsigned long long)va_arg(pm, unsigned int), *s, 'a');
	else if (*s == 'X')
		n += szputhex((unsigned long long)va_arg(pm, unsigned int), *s, 'A');
	else if (*s == '%')
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
			n += handle_arg(s, pm);
		}
		else
			n += write(1, s, 1);
		if (*s)
			s++;
	}
	va_end(pm);
	return (n);
}
