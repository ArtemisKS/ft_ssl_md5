/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_min.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:33:43 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:33:44 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		flen_prec(char **fs, t_spec *ts, char c)
{
	int j;

	j = 0;
	while (j < ts->f_len - (int)ts->prec)
		(*fs)[j++] = c;
	return (j);
}

char	*str_prec_width_uni(t_spec *ts, char *fs, char *is, char c)
{
	int fl;
	int n;
	int n_sum;
	int j;

	fl = 0;
	n = 0;
	n_sum = 0;
	j = 0;
	j = flen_prec(&fs, ts, ' ');
	n_sum = uni_cycle(ts, n_sum, &fl);
	while (!fl && n++ < n_sum)
		fs[j++] = c;
	uni_cycle_def(j, ts, &fs, is);
	return (fs);
}

int		flen_lenis(char **fs, char *is, char c, t_spec *ts)
{
	int j;

	j = 0;
	while (j < ts->f_len - (int)ft_strlen(is))
		(*fs)[j++] = c;
	return (j);
}

char	*str_noprec(t_spec *ts, char *fs, char *is)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (!ts->dot)
	{
		j = flen_lenis(&fs, is, ' ', ts);
		while (j < ts->f_len && j1 < (int)ft_strlen(is))
			fs[j++] = is[j1++];
	}
	else if (ts->dot && ft_strcmp(is, "^@"))
		while (j < (int)ts->width)
			fs[j++] = ' ';
	else
	{
		ft_strdel(&fs);
		fs = ft_strdup(is);
	}
	return (fs);
}

char	*handle_str_min(t_spec *ts, char *fs, char *is, char c)
{
	int j;

	j = 0;
	ts->f_len = figure_flen(ts);
	if (ts->prec != 0)
	{
		if (c == 's')
			fs = str_min_prec(ts, fs, is, &j);
		else if (c == 'S')
			j = str_min_prec_uni(ts, &fs, is);
		while (j < ts->f_len && (int)ft_strlen(is) != 0)
			fs[j++] = ' ';
		fs = str_min_prec_end(ts, fs, &j);
	}
	else
		fs = str_min_noprec(j, fs, is, ts);
	return (fs);
}
