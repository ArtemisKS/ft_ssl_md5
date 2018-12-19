/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 16:09:09 by akupriia          #+#    #+#             */
/*   Updated: 2018/10/28 03:06:08 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>

typedef struct	s_spec
{
	unsigned int	space : 1;
	unsigned int	hash : 1;
	unsigned int	min : 1;
	unsigned int	plus : 1;
	unsigned int	nil : 1;
	unsigned int	dot : 1;
	unsigned int	asterisk1 : 1;
	unsigned int	asterisk2 : 1;
	unsigned int	width;
	unsigned int	prec;
	unsigned int	hh : 1;
	unsigned int	h : 1;
	unsigned int	l : 1;
	unsigned int	ll : 1;
	unsigned int	j : 1;
	unsigned int	z : 1;
	int				f_len;
	int				len;
	int				fl;
	int				il;
	int				ia[100];
}				t_spec;

typedef struct	s_uni
{
	unsigned int	mask1;
	unsigned int	mask2;
	unsigned int	mask3;
	unsigned char	o4;
	unsigned char	o3;
	unsigned char	o2;
	unsigned char	o1;
}				t_uni;

int				max(int a, int b);
int				min(int a, int b);
char			*min_handle(char *is);
int				str_min_prec_uni(t_spec *ts, char **fs, char *is);
char			*str_min_prec(t_spec *ts, char *fs, char *is, int *j);
char			*str_min_prec_end(t_spec *ts, char *fs, int *j);
char			*str_min_prec_nil(t_spec *ts, char *fs, int *j);
char			*str_min_noprec(int j, char *fs, char *is, t_spec *ts);
int				figure_flen(t_spec *ts);
char			*f_leniter(char *fs, char *is, int *j, t_spec *ts);
char			*preciter(char *fs, char *is, int *j, t_spec *ts);
char			*str_prec_width(t_spec *ts, char *fs, char *is);
char			*str_prec_nowidth_uni(t_spec *ts, char *fs, char *is);
int				uni_cycle(t_spec *ts, int n_sum, int *fl);
void			uni_cycle_def(int j, t_spec *ts, char **fs, char *is);
int				flen_prec(char **fs, t_spec *ts, char c);
char			*str_prec_width_uni(t_spec *ts, char *fs, char *is, char c);
int				flen_lenis(char **fs, char *is, char c, t_spec *ts);
char			*str_noprec(t_spec *ts, char *fs, char *is);
char			*handle_str_min(t_spec *ts, char *fs, char *is, char c);
char			*handle_str_nmn_prec(t_spec *ts, char *fs, char *is, char c);
char			*handle_str_nomin_nil(t_spec *ts, char *fs, char *is, char c);
char			*handle_str_nil_prec(t_spec *ts, char *fs, char *is);
char			*handle_str_nil_noprec(t_spec *ts, char *fs, char *is);
char			*handle_str_nil_smprec(t_spec *ts, char *fs, char *is, char c);
char			*handle_str_nil(t_spec *ts, char *fs, char *is, char c);
char			*handle_str(t_spec *ts, char *s, char c);
char			*handle_dig_dot(t_spec *ts, char *fs);
char			*handle_dig_allnil(char *fs, char *is);
char			*f_leniterdig(int j, char *is, char *fs, t_spec *ts);
char			*handle_dig_nil(t_spec *ts, char *fs, char *is);
char			*dig_min_smprec(char *fs, char *is, t_spec *ts);
char			*dig_min_prec(t_spec *ts, char *fs, char *is);
char			*handle_dig_min(t_spec *ts, char *fs, char *is);
char			*dig_precwidth_smprec(char *fs, char *is, t_spec *ts);
char			*dig_precwidth_prec(t_spec *ts, char *fs, char *is);
char			*handle_dig_precwidth(t_spec *ts, char *fs, char *is);
char			*dig_plusnil_prec(t_spec *ts, char *fs, char *is, intmax_t i);
char			*dig_plusnil_noprec(char *fs, char *is, intmax_t i, t_spec *ts);
char			*handle_dig_plusnil(t_spec *ts, char *fs, char *is, intmax_t i);
char			*dig_pluswidth_prec(t_spec *ts, char *fs, char *is, intmax_t i);
char			*dig_pluswidth_noprec(char *f, char *s, intmax_t i, t_spec *t);
char			*handle_dig_pluswidth(t_spec *t, char *f, char *s, intmax_t i);
char			*dig_plminnil_prec(t_spec *ts, char *fs, char *is, intmax_t i);
char			*dig_plminnil_noprec(char *f, char *s, intmax_t i, t_spec *t);
char			*handle_dig_plminnil(t_spec *t, char *f, char *s, intmax_t i);
char			*handle_dig_plus(char *fs, char *is, intmax_t i, t_spec *ts);
char			*handle_dig_space(char *fs, char *is, t_spec *ts);
char			*dig_spaceminnil_prec(t_spec *ts, char *fs, char *is);
char			*dig_spaceminnil_noprec(char *fs, char *is, t_spec *ts);
char			*handle_dig_spaceminnil(t_spec *ts, char *fs, char *is);
char			*dig_spacenil_prec(t_spec *ts, char *fs, char *is);
char			*dig_spacenil_noprec(t_spec *ts, char *fs, char *is);
char			*handle_dig_spacenil(t_spec *ts, char *fs, char *is);
int				handle_dig1(t_spec *ts, intmax_t i, char **fs, char *is);
char			*uns_nil_prec(t_spec *ts, char *fs, char *is);
char			*handle_uns_nil(t_spec *ts, char *fs, char *is, uintmax_t i);
char			*uns_min_smprec(t_spec *ts, char *fs, char *is, uintmax_t i);
char			*uns_min_prec(t_spec *ts, char *fs, char *is);
char			*handle_uns_min(t_spec *ts, char *fs, char *is, uintmax_t i);
char			*handle_dig2(t_spec *ts, intmax_t i, char *fs, char *is);
char			*handle_dig(t_spec *ts, intmax_t i);
char			*handle_uns_dot(t_spec *ts, char *fs);
char			*handle_uns_allnil(t_spec *ts, char *fs, char *is, uintmax_t i);
char			*uns_nil_smprec(t_spec *ts, char *fs, char *is, uintmax_t i);
char			*uns_nominnil_smprec(t_spec *t, char *f, char *s, uintmax_t i);
char			*uns_nominnil_prec(t_spec *ts, char *fs, char *is, uintmax_t i);
char			*handle_uns_nominnil(t_spec *t, char *f, char *s, uintmax_t i);
char			*print_unsigned1(t_spec *ts, char *fs, char *is, uintmax_t i);
char			*print_unsigned(t_spec *ts, uintmax_t i, int fl);
char			*char_nominnil_prec(t_spec *ts, char *s, char *fs, int j);
char			*char_nominnil_noprec(char *s, char *fs, int j, t_spec *ts);
char			*handle_char_nominnil(t_spec *ts, char *s, char *fs);
int				char_nil_precwidth(t_spec *ts, char *s, char **fs);
char			*char_nil_noprec(char *s, char *fs, t_spec *ts);
char			*handle_char_nil(t_spec *ts, char *s, char *fs);
char			*char_min_prec(t_spec *ts, char *s, char *fs, int j);
char			*handle_char_min(t_spec *ts, char *s, char *fs);
char			*print_char(t_spec *ts, char *s);
char			*handle_digit(va_list ap, t_spec *ts, char c);
int				size_bin(int value);
char			*print_uni_7(int value, t_spec *ts, int i);
char			*print_uni_11(int value, t_spec *ts, int i, t_uni *tu);
char			*print_uni_16(int value, t_spec *ts, int i, t_uni *tu);
char			*print_uni_21(int value, t_spec *ts, int i, t_uni *tu);
t_uni			*init_uni(t_uni *tu);
char			*print_unicode(int value, t_spec *ts, int i);
char			*handle_string_uni(va_list ap, t_spec *ts, char *s);
char			*handle_string(va_list ap, t_spec *ts, char c);
char			*handle_char_uni(va_list ap, t_spec *ts, char *fs);
char			*handle_char(va_list ap, t_spec *ts, char c);
char			*handle_percent(t_spec *ts);
char			*ft_lower(char *fs);
char			*handle_unsigned1(va_list ap, t_spec *ts, char c, uintmax_t i);
char			*handle_unsigned(va_list ap, t_spec *ts, char c);
char			*point_at_beg1(char *fs, int j, int fl);
char			*point_at_beg(char *fs, t_spec *ts);
int				cor_pointer1(int i, char **fs, t_spec *ts);
char			*cor_pointer(char *fs, t_spec *ts);
char			*handle_pointer(va_list ap, t_spec *ts);
char			*print_format(va_list ap, t_spec *ts, char c);
void			init_struct(t_spec *ts);
int				parse_width(char *fmt, t_spec *ts);
int				parse_pres(char *fmt, t_spec *ts);
int				parse_flags(char *fmt, t_spec *ts);
int				parse_width_bon(char *fmt, t_spec *ts, int i, va_list ap);
int				parse_width_bon1(char *fmt, t_spec *ts, int i, va_list ap);
int				parse_prec_bon(char *fmt, t_spec *ts, int i, va_list ap);
int				parse_specif(char *fmt, t_spec *ts, int *i);
int				parse_specif1(char *fmt, t_spec *ts, int i);
int				parse_spec(char *fmt, t_spec *ts, va_list ap);
int				is_type(char c);
int				str_zero(char *fs);
int				output_fstring1(char *s, int fl, int j);
int				output_fstring(va_list ap, char c, int j, t_spec *ts);
int				parse_format(int fd, va_list ap, char *fmt);
int				ft_printf(char *fmt, ...);
int				ft_dprintf(int fd, char *fmt, ...);

#endif
