/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:09:29 by ldecavel          #+#    #+#             */
/*   Updated: 2025/09/14 14:39:04 by ldecavel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

typedef unsigned char		t_u8;
typedef unsigned long long	t_ull;
typedef long long			t_ll;

# define FMN 1
# define FZR 2
# define FHS 4
# define FPL 8
# define FSP 16

typedef struct t_format
{
	short	flags;
	int		wid;
	int		pre;
	int		zer;
	int		pad;
	int		n;
	t_ll	v;
}			t_format;

int		ft_printf(const char *s, ...);
//szput_fd
int		szputpm_fd(int fd, va_list pm, char c, int n);
//format
int		format(char c, va_list pm, t_format *f);
//utils
int		sm_atoii(char **nptr);
char	*ft_strchr(const char *s, int c);
int		max(int a, int b);
int		min(int a, int b);

#endif
