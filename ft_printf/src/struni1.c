/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struni1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:29:12 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:29:13 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*preciter(char *fs, char *is, int *j, t_spec *ts)
{
	int j1;

	j1 = 0;
	while (*j < (int)ts->prec && j1 < (int)ft_strlen(is))
		fs[(*j)++] = is[j1++];
	return (fs);
}

char	*str_prec_width(t_spec *ts, char *fs, char *is)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (is[0] && ts->width)
	{
		ts->f_len = max(ts->width, (int)ft_strlen(is));
		while (j < ts->f_len - (int)ts->prec)
			fs[j++] = ' ';
		while (j < ts->f_len - (int)ft_strlen(is))
			fs[j++] = ' ';
		while (j < ts->f_len && j1 < (int)ft_strlen(is))
			fs[j++] = is[j1++];
	}
	else if (!ts->width)
		fs = f_leniter(fs, is, &j, ts);
	else
		fs = str_min_prec_end(ts, fs, &j);
	return (fs);
}

char	*str_prec_nowidth_uni(t_spec *ts, char *fs, char *is)
{
	int n;
	int cnt;
	int n_sum;
	int j;
	int j1;

	n = 0;
	cnt = 0;
	n_sum = 0;
	j = 0;
	j1 = 0;
	while (j < (int)ts->prec)
	{
		if ((n_sum += ts->ia[n]) > (int)ts->prec)
			break ;
		while (cnt < ts->ia[n])
		{
			fs[j++] = is[j1++];
			cnt++;
		}
		n++;
		cnt = 0;
	}
	return (fs);
}

int		uni_cycle(t_spec *ts, int n_sum, int *fl)
{
	int n;

	n = 0;
	while (ts->ia[n])
	{
		n_sum += ts->ia[n];
		if (n_sum == (int)ts->prec)
			*fl = 1;
		else if (n_sum > (int)ts->prec)
		{
			if (ts->ia[n - 1])
			{
				n_sum -= ts->ia[n];
				if (ts->ia[n - 1] + n_sum <= (int)ts->prec)
					n_sum = ts->ia[n - 1];
				else
					n_sum = (int)ts->prec - ts->ia[n - 1];
			}
			else
				n_sum -= (int)ts->prec;
			break ;
		}
		n++;
	}
	return (n_sum);
}

void	uni_cycle_def(int j, t_spec *ts, char **fs, char *is)
{
	int n;
	int n_sum;
	int j1;
	int cnt;

	n = 0;
	n_sum = 0;
	j1 = 0;
	cnt = 0;
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
	{
		if ((n_sum += ts->ia[n]) > (int)ts->prec)
		{
			while (j < ts->f_len)
				(*fs)[j++] = ' ';
			break ;
		}
		while (cnt < ts->ia[n])
		{
			(*fs)[j++] = is[j1++];
			cnt++;
		}
		n++;
		cnt = 0;
	}
}
