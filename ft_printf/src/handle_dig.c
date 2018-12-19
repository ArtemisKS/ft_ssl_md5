/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:49:44 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:50:00 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_dig2(t_spec *ts, intmax_t i, char *fs, char *is)
{
	if (!ts->plus && !ts->min && !ts->nil && !ts->space && i >= 0)
		fs = handle_dig_precwidth(ts, fs, is);
	else if ((ts->plus && !ts->min && ts->nil) ||
		(i < 0 && !ts->min && ts->nil))
		fs = handle_dig_plusnil(ts, fs, is, i);
	else if ((ts->plus && !ts->min && ts->width) ||
		(i < 0 && !ts->min && ts->width))
		fs = handle_dig_pluswidth(ts, fs, is, i);
	else if ((ts->plus && ts->min && ts->nil) ||
		(i < 0 && ts->min && ts->nil) ||
		(ts->plus && ts->min && ts->width) ||
		(i < 0 && ts->min && ts->width))
		fs = handle_dig_plminnil(ts, fs, is, i);
	else if ((ts->plus && !ts->nil && !ts->width) ||
		(i < 0 && !ts->nil && !ts->width))
		fs = handle_dig_plus(fs, is, i, ts);
	else if (!ts->plus && ts->space && !ts->nil && !ts->width && i >= 0)
		fs = handle_dig_space(fs, is, ts);
	else if ((!ts->plus && ts->space && ts->min && ts->nil && i >= 0)
		|| (!ts->plus && ts->space && ts->min && ts->width && i >= 0))
		fs = handle_dig_spaceminnil(ts, fs, is);
	else if ((!ts->plus && ts->space && !ts->min && ts->nil && i >= 0)
			|| (!ts->plus && ts->space && !ts->min && ts->width && i >= 0))
		fs = handle_dig_spacenil(ts, fs, is);
	return (fs);
}

char	*handle_dig(t_spec *ts, intmax_t i)
{
	char *fs;
	char *is;

	is = ft_itoa_base(i, 10);
	if (i < 0)
		is = min_handle(is);
	if (ts->asterisk2 && ts->min && (int)ts->prec > (int)ft_strlen(is))
	{
		ts->prec = 0;
		if (ts->nil)
			ts->min = 0;
	}
	ts->f_len = max(max((int)ft_strlen(is), ts->width), ts->prec);
	fs = (char *)ft_strnew(2 * ts->f_len);
	if (!handle_dig1(ts, i, &fs, is))
		fs = handle_dig2(ts, i, fs, is);
	ft_strdel(&is);
	return (fs);
}

char	*handle_uns_dot(t_spec *ts, char *fs)
{
	int j;

	j = 0;
	if ((!ts->width && !ts->hash) || (!ts->width && ts->hash && ts->fl != 1))
	{
		fs[0] = 0;
		return (fs);
	}
	else
	{
		if (ts->hash && ts->fl == 1)
			fs[j++] = '0';
		while (j < ts->f_len)
			fs[j++] = ' ';
	}
	return (fs);
}

char	*handle_uns_allnil(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	if (ts->hash == 1 && ts->fl == 2 && i != 0)
	{
		fs[j++] = '0';
		fs[j++] = 'X';
		ts->il += 2;
	}
	else if (ts->hash == 1 && ts->fl == 1 && i != 0)
	{
		fs[j++] = '0';
		ts->il++;
	}
	while (j < ts->il && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*uns_nil_smprec(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	if (ts->hash == 1 && ts->fl == 2 && i != 0)
	{
		fs[j++] = '0';
		fs[j++] = 'X';
		if ((int)ts->width < ts->il)
			ts->f_len += 2;
	}
	else if (ts->hash == 1 && ts->fl == 1 && i != 0)
	{
		fs[j++] = '0';
		if ((int)ts->width < ts->il)
			ts->f_len++;
	}
	while (j < ts->f_len - ts->il)
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}
