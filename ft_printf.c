/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:38:50 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/14 15:00:52 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
