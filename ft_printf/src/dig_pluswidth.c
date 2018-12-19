/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dig_pluswidth.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:43:58 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:43:59 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*dig_pluswidth_prec(t_spec *ts, char *fs, char *is, intmax_t i)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	while (j < ts->f_len - max((int)ft_strlen(is), ts->prec))
		fs[j++] = ' ';
	while (j < ts->f_len - (int)ft_strlen(is))
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (fs[j--] != ' ')
		;
	if (i >= 0)
		fs[++j] = '+';
	else
		fs[++j] = '-';
	return (fs);
}

char	*dig_pluswidth_noprec(char *fs, char *is, intmax_t i, t_spec *ts)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	while (j < ts->f_len - (int)ft_strlen(is))
		fs[j++] = ' ';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (fs[j] != ' ')
		j--;
	if (i >= 0)
		fs[j++] = '+';
	else
		fs[j++] = '-';
	return (fs);
}

char	*handle_dig_pluswidth(t_spec *ts, char *fs, char *is, intmax_t i)
{
	if ((int)ts->width < ts->f_len)
		ts->f_len++;
	if (ts->prec)
		fs = dig_pluswidth_prec(ts, fs, is, i);
	else
		fs = dig_pluswidth_noprec(fs, is, i, ts);
	return (fs);
}

char	*dig_plminnil_prec(t_spec *ts, char *fs, char *is, intmax_t i)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (i >= 0)
		fs[j++] = '+';
	else
		fs[j++] = '-';
	while (j < (int)(ts->prec - (int)ft_strlen(is) + 1))
		fs[j++] = '0';
	while (j < (int)(ts->prec + 1) && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

char	*dig_plminnil_noprec(char *fs, char *is, intmax_t i, t_spec *ts)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (i >= 0)
		fs[j++] = '+';
	else
		fs[j++] = '-';
	j1 = 0;
	while (j1 < (int)ft_strlen(is) && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}
