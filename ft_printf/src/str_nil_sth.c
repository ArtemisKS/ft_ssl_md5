/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_nil_sth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:35:24 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:35:25 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_str_nmn_prec(t_spec *ts, char *fs, char *is, char c)
{
	int j;

	j = 0;
	if (ts->width)
	{
		ts->f_len = max(ts->prec, ts->width);
		j = flen_prec(&fs, ts, ' ');
		if (c == 's')
			fs = f_leniter(fs, is, &j, ts);
		else if (c == 'S')
			fs = str_prec_width_uni(ts, fs, is, ' ');
	}
	else
	{
		if (c == 's')
			fs = str_min_prec(ts, fs, is, &j);
		else if (c == 'S')
			fs = str_prec_nowidth_uni(ts, fs, is);
	}
	return (fs);
}

char	*handle_str_nomin_nil(t_spec *ts, char *fs, char *is, char c)
{
	ts->f_len = figure_flen(ts);
	if ((int)ts->prec > (int)ft_strlen(is))
		fs = str_prec_width(ts, fs, is);
	else
	{
		if (!ts->prec)
			fs = str_noprec(ts, fs, is);
		else
			fs = handle_str_nmn_prec(ts, fs, is, c);
	}
	return (fs);
}

char	*handle_str_nil_prec(t_spec *ts, char *fs, char *is)
{
	int j;

	j = 0;
	if (ts->width != 0)
	{
		while (j < ts->f_len - (int)ts->prec)
			fs[j++] = '0';
		while (j < ts->f_len - (int)ft_strlen(is))
			fs[j++] = '0';
		fs = f_leniter(fs, is, &j, ts);
	}
	else if (!ts->width)
		fs = f_leniter(fs, is, &j, ts);
	else
		str_min_prec_nil(ts, fs, &j);
	return (fs);
}

char	*handle_str_nil_noprec(t_spec *ts, char *fs, char *is)
{
	int j;

	j = 0;
	if (!ts->dot)
	{
		j = flen_lenis(&fs, is, '0', ts);
		fs = f_leniter(fs, is, &j, ts);
	}
	else if (ts->dot && ft_strcmp(is, "^@"))
		while (j < (int)ts->width)
			fs[j++] = '0';
	else
	{
		ft_strdel(&fs);
		fs = ft_strdup(is);
	}
	return (fs);
}

char	*handle_str_nil_smprec(t_spec *ts, char *fs, char *is, char c)
{
	int j;

	j = 0;
	if (ts->width)
	{
		j = flen_prec(&fs, ts, '0');
		if (c == 's')
			fs = f_leniter(fs, is, &j, ts);
		else if (c == 'S')
			fs = str_prec_width_uni(ts, fs, is, '0');
	}
	else
	{
		if (c == 's')
			fs = preciter(fs, is, &j, ts);
		else if (c == 'S')
			fs = str_prec_nowidth_uni(ts, fs, is);
	}
	return (fs);
}
