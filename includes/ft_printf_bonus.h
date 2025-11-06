/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldecavel <ldecavel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:09:29 by ldecavel          #+#    #+#             */
/*   Updated: 2025/11/06 17:41:54 by ldecavel         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdbool.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>

# define FMN 1
# define FZR 2
# define FHS 4
# define FPL 8
# define FSP 16

typedef struct s_printf
{
	va_list	pm;
	int		n;
	int		cur;
}			t_printf;

typedef struct s_format
{
	short	flags;
	int		wid;
	int		pre;
	int		zer;
	int		pad;
	int		n;
	int64_t	v;
}			t_format;

int		ft_printf(const char *s, ...) __attribute__((format(printf, 1, 2)));
//szput_en
int		szputpm_en(int en, va_list pm, char c, int n);
//format
int		format(char c, va_list pm, t_format *f);
//utils
int		sm_atoii(char **nptr);
char	*ft_strchr(const char *s, int c);
int		max(int a, int b);
int		min(int a, int b);

#endif
