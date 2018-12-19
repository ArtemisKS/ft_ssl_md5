/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dig_min.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:40:40 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:40:42 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_dig_nil(t_spec *ts, char *fs, char *is)
{
	int j;

	j = 0;
	if ((int)ts->prec >= (int)ft_strlen(is))
		while (j < ts->f_len - (int)ts->prec)
		{
			fs[j] = ' ';
			j++;
		}
	while (j < ts->f_len - (int)ft_strlen(is))
	{
		fs[j] = '0';
		j++;
	}
	fs = f_leniterdig(j, is, fs, ts);
	return (fs);
}

char	*dig_min_smprec(char *fs, char *is, t_spec *ts)
{
	int j1;
	int j;

	j = 0;
	j1 = 0;
	while (j < (int)ft_strlen(is) && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

char	*dig_min_prec(t_spec *ts, char *fs, char *is)
{
	int j1;
	int j;

	j = 0;
	j1 = 0;
	while (j < (int)(ts->prec - (int)ft_strlen(is)))
		fs[j++] = '0';
	while (j < (int)ts->prec && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

char	*handle_dig_min(t_spec *ts, char *fs, char *is)
{
	if ((int)ts->prec <= (int)ft_strlen(is))
		fs = dig_min_smprec(fs, is, ts);
	else
		fs = dig_min_prec(ts, fs, is);
	return (fs);
}

char	*dig_precwidth_smprec(char *fs, char *is, t_spec *ts)
{
	int j1;
	int j;

	j1 = 0;
	j = 0;
	while (j < ts->f_len - (int)ft_strlen(is))
		fs[j++] = ' ';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}
