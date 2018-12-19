/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:25:40 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:25:41 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		max(int a, int b)
{
	return (a > b ? a : b);
}

int		min(int a, int b)
{
	return (a < b ? a : b);
}

char	*min_handle(char *is)
{
	int		i;
	char	*res;
	int		fl;
	int		j;

	i = 1;
	fl = 0;
	j = 0;
	res = (char *)ft_strnew(ft_strlen(is));
	while (is[i])
	{
		if (is[i] > '0' && is[i] <= '9')
			fl = 1;
		if (fl)
			res[j++] = is[i];
		i++;
	}
	return (res);
}

int		str_min_prec_uni(t_spec *ts, char **fs, char *is)
{
	int j1;
	int n;
	int cnt;
	int n_sum;
	int j;

	j1 = 0;
	n = 0;
	cnt = 0;
	n_sum = 0;
	j = 0;
	while (j < (int)ts->prec)
	{
		if ((n_sum += ts->ia[n]) > (int)ts->prec)
			break ;
		while (cnt < ts->ia[n] && j1 < (int)ft_strlen(is))
		{
			(*fs)[j++] = is[j1++];
			cnt++;
		}
		n++;
		cnt = 0;
	}
	return (j);
}

char	*str_min_prec(t_spec *ts, char *fs, char *is, int *j)
{
	int j1;

	j1 = 0;
	while (*j < (int)ts->prec && j1 < (int)ft_strlen(is))
		fs[(*j)++] = is[j1++];
	return (fs);
}
