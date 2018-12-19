/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dig_plusnil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:42:20 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:42:21 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*dig_precwidth_prec(t_spec *ts, char *fs, char *is)
{
	int j1;
	int j;

	j1 = 0;
	j = 0;
	while (j < (int)(ts->f_len - ts->prec))
		fs[j++] = ' ';
	while (j < ts->f_len - (int)ft_strlen(is))
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*handle_dig_precwidth(t_spec *ts, char *fs, char *is)
{
	if ((int)ts->prec <= (int)ft_strlen(is))
		fs = dig_precwidth_smprec(fs, is, ts);
	else
		fs = dig_precwidth_prec(ts, fs, is);
	return (fs);
}

char	*dig_plusnil_prec(t_spec *ts, char *fs, char *is, intmax_t i)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (ts->prec > ts->width)
		ts->f_len++;
	while (j < ts->f_len - max((int)ft_strlen(is), ts->prec))
		fs[j++] = ' ';
	while (j < ts->f_len - (int)ft_strlen(is))
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (fs[j] != ' ' && j-- >= -1)
		;
	if (i >= 0)
		fs[j] = '+';
	else
		fs[j] = '-';
	return (fs);
}

char	*dig_plusnil_noprec(char *fs, char *is, intmax_t i, t_spec *ts)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (i >= 0)
		fs[j++] = '+';
	else
		fs[j++] = '-';
	while (j < ts->f_len - (int)ft_strlen(is))
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*handle_dig_plusnil(t_spec *ts, char *fs, char *is, intmax_t i)
{
	if (ts->f_len == (int)ft_strlen(is))
		ts->f_len++;
	if (ts->prec)
		fs = dig_plusnil_prec(ts, fs, is, i);
	else
		fs = dig_plusnil_noprec(fs, is, i, ts);
	return (fs);
}
