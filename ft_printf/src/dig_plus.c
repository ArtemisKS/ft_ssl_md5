/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dig_plus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:45:36 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:45:37 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_dig_plminnil(t_spec *ts, char *fs, char *is, intmax_t i)
{
	if (ts->prec)
		fs = dig_plminnil_prec(ts, fs, is, i);
	else
		fs = dig_plminnil_noprec(fs, is, i, ts);
	return (fs);
}

char	*handle_dig_plus(char *fs, char *is, intmax_t i, t_spec *ts)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	ts->f_len++;
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

char	*handle_dig_space(char *fs, char *is, t_spec *ts)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	if ((int)ft_strlen(is) == ts->f_len)
		ts->f_len++;
	fs[j++] = ' ';
	while (j < ts->f_len - (int)ft_strlen(is))
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*dig_spaceminnil_prec(t_spec *ts, char *fs, char *is)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	fs[j++] = ' ';
	while (j < ts->f_len - max((int)ft_strlen(is), ts->prec))
		fs[j++] = '0';
	while (j < ts->f_len - (max((int)ft_strlen(is), ts->prec) -
		min((int)ft_strlen(is), ts->prec)) && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

char	*dig_spaceminnil_noprec(char *fs, char *is, t_spec *ts)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	fs[j++] = ' ';
	while (j1 < (int)ft_strlen(is) && j < ts->f_len)
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}
