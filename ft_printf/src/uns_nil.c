/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uns_nil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:51:09 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:51:09 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*uns_nil_prec(t_spec *ts, char *fs, char *is)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	while (j < ts->f_len - (int)ts->prec)
		fs[j++] = ' ';
	while (j < ts->f_len - ts->il)
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*handle_uns_nil(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	if ((int)ts->prec <= ts->il)
		fs = uns_nil_smprec(ts, fs, is, i);
	else
		fs = uns_nil_prec(ts, fs, is);
	return (fs);
}

char	*uns_min_smprec(t_spec *ts, char *fs, char *is, uintmax_t i)
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
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

char	*uns_min_prec(t_spec *ts, char *fs, char *is)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	while (j < (int)(ts->prec - ts->il))
		fs[j++] = '0';
	while (j < (int)ts->prec && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

char	*handle_uns_min(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	if ((int)ts->prec <= ts->il)
		fs = uns_min_smprec(ts, fs, is, i);
	else
		fs = uns_min_prec(ts, fs, is);
	return (fs);
}
