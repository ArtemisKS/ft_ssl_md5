/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_nil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:36:59 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:37:00 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_str_nil(t_spec *ts, char *fs, char *is, char c)
{
	ts->f_len = figure_flen(ts);
	if ((int)ts->prec > (int)ft_strlen(is))
		fs = handle_str_nil_prec(ts, fs, is);
	else
	{
		if (!ts->prec)
			fs = handle_str_nil_noprec(ts, fs, is);
		else
			fs = handle_str_nil_smprec(ts, fs, is, c);
	}
	return (fs);
}

char	*handle_str(t_spec *ts, char *s, char c)
{
	char *fs;
	char *is;

	if (s)
		is = ft_strdup(s);
	else
		is = ft_strdup("");
	if (ts->asterisk2 && ts->min && (int)ts->prec > (int)ft_strlen(is))
		ts->prec = 0;
	ts->f_len = max(ft_strlen(is), ts->width);
	fs = (char *)ft_strnew(2 * ts->f_len);
	if (ts->min == 1)
		fs = handle_str_min(ts, fs, is, c);
	else if (ts->min == 0 && ts->nil == 0)
		fs = handle_str_nomin_nil(ts, fs, is, c);
	else if (ts->min == 0 && ts->nil == 1)
		fs = handle_str_nil(ts, fs, is, c);
	ft_strdel(&is);
	return (fs);
}

char	*handle_dig_dot(t_spec *ts, char *fs)
{
	int j;

	j = 0;
	if (ts->width == 0)
	{
		fs[j] = 0;
		return (fs);
	}
	else
	{
		while (j < ts->f_len)
			fs[j++] = ' ';
	}
	return (fs);
}

char	*handle_dig_allnil(char *fs, char *is)
{
	int j;

	j = 0;
	while (j < (int)ft_strlen(is))
	{
		fs[j] = is[j];
		j++;
	}
	return (fs);
}

char	*f_leniterdig(int j, char *is, char *fs, t_spec *ts)
{
	int j1;

	j1 = 0;
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
	{
		fs[j++] = is[j1];
		j1++;
	}
	return (fs);
}
