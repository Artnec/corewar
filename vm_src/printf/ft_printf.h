/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:51:45 by anesteru          #+#    #+#             */
/*   Updated: 2018/01/05 16:51:48 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct	s_flags
{
	int			type;
	int			width;
	int			precision;
	int			length;
	int			minus;
	int			plus;
	int			hash;
	int			space;
	int			zero;
	int			wc;
	int			error;
}				t_flags;

int				ft_printf(const char *fmt, ...);

int				put_wide_char_space_zero(wchar_t wc, t_flags *sd);
int				put_wide_str(wchar_t *str, t_flags *sd);
int				put_str_char(va_list argp, t_flags *sd);
int				put_no_type(const char **fmt, t_flags *sd);
int				put_signed_num(t_flags *sd, va_list argp);
int				put_unsigned_num(t_flags *sd, va_list argp);
void			initialize_structure(t_flags *sd);
int				is_type(const char *s);
int				ft_atoi(const char **str, va_list argp);
int				put_space_or_zero(int width, int zero);
int				num_len(size_t num, unsigned int base, int precision);

#endif
