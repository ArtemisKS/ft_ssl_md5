/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:57:16 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:57:18 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_char_nil(t_spec *ts, char *s, char *fs)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (ts->prec)
	{
		if (ts->width)
			j = char_nil_precwidth(ts, s, &fs);
		if (s[0])
			while (j < ts->f_len && j1 < (int)ft_strlen(s))
				fs[j++] = s[j1++];
		else
		{
			if (ts->f_len != (int)ts->prec)
				while (j < ts->f_len)
					fs[j++] = '0';
			fs[j++] = '^';
			fs[j] = '@';
		}
	}
	else
		fs = char_nil_noprec(s, fs, ts);
	return (fs);
}

char	*char_min_prec(t_spec *ts, char *s, char *fs, int j)
{
	int j1;

	j1 = 0;
	if (s[0])
	{
		j1 = 0;
		if (!s[1])
			while (j < (int)ts->prec && j1 < (int)ft_strlen(s))
				fs[j++] = s[j1++];
		else
			while (j < ts->f_len && j1 < (int)ft_strlen(s))
				fs[j++] = s[j1++];
		while (j < ts->f_len)
			fs[j++] = ' ';
	}
	else
	{
		if (ts->f_len != (int)ts->prec)
			while (j < ts->f_len)
				fs[j++] = ' ';
		fs[j++] = '^';
		fs[j] = '@';
	}
	return (fs);
}

char	*handle_char_min(t_spec *ts, char *s, char *fs)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (ts->prec)
		fs = char_min_prec(ts, s, fs, j);
	else
	{
		if (s[0])
			while (j < ts->f_len && j1 < (int)ft_strlen(s))
				fs[j++] = s[j1++];
		else
		{
			fs[j++] = '^';
			fs[j++] = '@';
		}
		while (j < ts->f_len)
			fs[j++] = ' ';
	}
	return (fs);
}

char	*print_char(t_spec *ts, char *s)
{
	int		len;
	char	*fs;

	len = ft_strlen(s);
	if (!s[0])
		len = 1;
	ts->f_len = max(len, ts->width);
	ts->len = len;
	fs = (char *)ft_strnew(2 * ts->f_len);
	if (ts->min == 0 && ts->nil == 0)
		fs = handle_char_nominnil(ts, s, fs);
	else if (ts->min == 0 && ts->nil == 1)
		fs = handle_char_nil(ts, s, fs);
	else if (ts->min == 1)
		fs = handle_char_min(ts, s, fs);
	return (fs);
}

char	*handle_digit(va_list ap, t_spec *ts, char c)
{
	intmax_t	i;
	char		*fs;

	if (c == 'D')
		ts->l = 1;
	if (ts->l == 1)
		i = va_arg(ap, long int);
	else if (ts->ll == 1)
		i = va_arg(ap, long long int);
	else if (ts->h == 1)
		i = (short int)va_arg(ap, int);
	else if (ts->hh)
		i = (char)va_arg(ap, int);
	else if (ts->z == 1)
		i = va_arg(ap, ssize_t);
	else if (ts->j == 1)
		i = va_arg(ap, intmax_t);
	else
		i = va_arg(ap, int);
	fs = handle_dig(ts, i);
	return (fs);
}
