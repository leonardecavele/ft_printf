/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:09:29 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/12 03:26:53 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

//utils
int	szputchar(char c);
int	szputstr(const char *s);
int	szputnbr(long long n);
int	szputhex(unsigned long long n, char c, char a);

#endif
