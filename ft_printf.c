/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:38:50 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/11 22:59:00 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

static int	handle_arg(const char *s, va_list pm, int n)
{
	if (*s == 'c')
		n += szputchar(va_arg(pm, int));
	else if (*s == 's')
		n += szputstr((char *)va_arg(pm, const char *));
	else if (*s == 'd' || *s == 'i')
		n += szputnbr(va_arg(pm, int));
	else
		return (-1);
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
			n = handle_arg(s, pm, n);
		}
		else
			n += write(1, s, 1);
		if (*s)
			s++;
	}
	va_end(pm);
	return (n);
}

int	main(void)
{
	return (ft_printf("%d\n", ft_printf("salut %s %d\n", "oui", 335)));
}
