/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:53:46 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:53:47 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*uns_nominnil_smprec(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	if (ts->hash == 1 && ts->fl == 2)
		ts->il += 2;
	else if (ts->hash == 1 && ts->fl == 1)
		ts->il++;
	while (j < ts->f_len - ts->il)
		fs[j++] = ' ';
	if (ts->hash == 1 && ts->fl == 2 && i != 0)
	{
		fs[j++] = '0';
		fs[j++] = 'X';
	}
	else if (ts->hash == 1 && ts->fl == 1 && i != 0)
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*uns_nominnil_prec(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	while (j < (int)(ts->f_len - ts->prec))
		fs[j++] = ' ';
	if (ts->hash == 1 && ts->fl == 2 && i != 0)
	{
		fs[j++] = '0';
		fs[j++] = 'X';
		ts->f_len += 2;
	}
	else if (ts->hash == 1 && ts->fl == 1 && i != 0)
		fs[j++] = '0';
	while (j < ts->f_len - ts->il)
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*handle_uns_nominnil(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	if ((int)ts->prec <= ts->il)
		fs = uns_nominnil_smprec(ts, fs, is, i);
	else
		fs = uns_nominnil_prec(ts, fs, is, i);
	return (fs);
}

char	*print_unsigned1(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	if (ts->dot == 1 && ts->prec == 0 && i == 0)
		fs = handle_uns_dot(ts, fs);
	else if (ts->min == 0 && ts->nil == 0 && ts->width == 0 && ts->prec == 0)
		fs = handle_uns_allnil(ts, fs, is, i);
	else if (ts->nil == 1 && ts->min == 0)
		fs = handle_uns_nil(ts, fs, is, i);
	else if (ts->min == 1)
		fs = handle_uns_min(ts, fs, is, i);
	else if (ts->min == 0 && ts->nil == 0)
		fs = handle_uns_nominnil(ts, fs, is, i);
	return (fs);
}

char	*print_unsigned(t_spec *ts, uintmax_t i, int fl)
{
	char	*fs;
	int		il;
	char	*is;

	if (!fl)
		il = ft_nbrlen_u(i);
	else if (fl == 1)
	{
		is = ft_itoa_base_u(i, 8);
		il = ft_strlen(is);
	}
	else
	{
		is = ft_itoa_base_u(i, 16);
		il = ft_strlen(is);
	}
	ts->f_len = max(max(il, ts->width), ts->prec);
	ts->fl = fl;
	ts->il = il;
	if (!fl)
		is = ft_itoa_base_u(i, 10);
	fs = (char *)ft_strnew(2 * ts->f_len);
	fs = print_unsigned1(ts, fs, is, i);
	ft_strdel(&is);
	return (fs);
}
