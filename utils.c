/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:03:57 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/13 21:46:07 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	sm_atoii(char **nptr)
{
	long	result;

	result = 0;
	while (**nptr >= '0' && **nptr <= '9')
	{
		result *= 10;
		result += **nptr - '0';
		(*nptr)++;
	}
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if ((t_u8)(*s) == (t_u8)c)
			return ((char *)s);
		s++;
	}
	if (!(t_u8)c)
		return ((char *)s);
	return (0);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
