/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dig1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:47:21 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:47:22 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_dig_spaceminnil(t_spec *ts, char *fs, char *is)
{
	if (ts->prec)
		fs = dig_spaceminnil_prec(ts, fs, is);
	else
		fs = dig_spaceminnil_noprec(fs, is, ts);
	return (fs);
}

char	*dig_spacenil_prec(t_spec *ts, char *fs, char *is)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	while (j < ts->f_len - max((int)ft_strlen(is), ts->prec))
		fs[j++] = ' ';
	while (j < ts->f_len - min((int)ft_strlen(is), ts->prec))
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*dig_spacenil_noprec(t_spec *ts, char *fs, char *is)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	fs[j++] = ' ';
	while (j < ts->f_len - (int)ft_strlen(is) && ts->nil)
		fs[j++] = '0';
	while (j < ts->f_len - (int)ft_strlen(is) && !ts->nil)
		fs[j++] = ' ';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*handle_dig_spacenil(t_spec *ts, char *fs, char *is)
{
	if (ts->prec)
		fs = dig_spacenil_prec(ts, fs, is);
	else
		fs = dig_spacenil_noprec(ts, fs, is);
	return (fs);
}

int		handle_dig1(t_spec *ts, intmax_t i, char **fs, char *is)
{
	if (ts->dot && !ts->prec && i == 0)
	{
		*fs = handle_dig_dot(ts, *fs);
		return (1);
	}
	else if (!ts->min && !ts->space && !ts->plus
		&& !ts->nil && !ts->width && !ts->prec && i >= 0)
	{
		*fs = handle_dig_allnil(*fs, is);
		return (1);
	}
	else if (ts->nil && !ts->min && !ts->plus && !ts->space && i >= 0)
	{
		*fs = handle_dig_nil(ts, *fs, is);
		return (1);
	}
	else if (ts->min && !ts->plus && !ts->space && i >= 0)
	{
		*fs = handle_dig_min(ts, *fs, is);
		return (1);
	}
	return (0);
}
