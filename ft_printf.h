/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:09:29 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/13 00:06:06 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

# define M_F 1
# define Z_F 2
# define H_F 4
# define S_F 8
# define P_F 16

typedef unsigned long long	t_ull;
typedef long long			t_ll;

typedef struct s_flags
{
	int	f;
	int	w;
	int	p;
	int	z;
	int	n;
	int	d;
}		t_flags;

int	ft_printf(const char *s, ...);

//szput
int	szputchar(char c, int fd);
int	szputnstr(const char *s, int fd, int n);
int	szputnbr(t_ll n, int fd);
int	szputhex(t_ull n, char c, char a, int fd);
int	szputpm(char c, va_list pm, int fd, int n);

//utils
int	sm_atoii(char **nptr);
int	max(int a, int b);

#endif
