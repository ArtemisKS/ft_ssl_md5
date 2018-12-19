/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stfunc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:28:11 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:28:12 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*str_min_prec_end(t_spec *ts, char *fs, int *j)
{
	if (ts->f_len != (int)ts->prec)
		while (*j < ts->f_len)
			fs[(*j)++] = ' ';
	return (fs);
}

char	*str_min_prec_nil(t_spec *ts, char *fs, int *j)
{
	if (ts->f_len != (int)ts->prec)
		while (*j < ts->f_len)
			fs[(*j)++] = '0';
	return (fs);
}

char	*str_min_noprec(int j, char *fs, char *is, t_spec *ts)
{
	int j1;

	j1 = 0;
	while (j < (int)ft_strlen(is) && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

int		figure_flen(t_spec *ts)
{
	if (ts->prec != 0 && ts->width != 0)
		ts->f_len = max(ts->prec, ts->width);
	else if (ts->prec != 0)
		ts->f_len = ts->prec;
	return (ts->f_len);
}

char	*f_leniter(char *fs, char *is, int *j, t_spec *ts)
{
	int j1;

	j1 = 0;
	while (*j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[(*j)++] = is[j1++];
	return (fs);
}
