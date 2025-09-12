/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:03:57 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/13 00:32:26 by ldecavel         ###   ########.fr       */
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

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
