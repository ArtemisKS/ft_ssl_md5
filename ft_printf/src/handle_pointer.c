/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 18:02:55 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 18:02:56 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*point_at_beg1(char *fs, int j, int fl)
{
	int i;

	i = 0;
	while (i < fl)
	{
		if (i == 0)
			fs[i] = '0';
		else if (i == 1)
			fs[i] = 'x';
		else if (i > 1 && j)
			fs[i] = '0';
		else if (i > 1)
			fs[i] = ' ';
		if (fs[i] == '0' && i != 0)
			j--;
		i++;
	}
	return (fs);
}

char	*point_at_beg(char *fs, t_spec *ts)
{
	int i;
	int j;
	int fl;

	j = 0;
	i = 0;
	while (fs[i++] == '0')
		j++;
	fl = max(ts->prec, ts->width);
	if (fl == (int)ts->prec)
		fl += 2;
	fs = ft_strnew(fl);
	fs = point_at_beg1(fs, j, fl);
	return (fs);
}

int		cor_pointer1(int i, char **fs, t_spec *ts)
{
	int fl;

	fl = 1;
	if (i == (int)ft_strlen(*fs) - 1 && !((*fs)[i + 1]))
		*fs = ft_strjoin(*fs, "x0");
	else if (fs[0] == 0)
		*fs = ft_strdup("0x");
	else if (i == 0)
		*fs = point_at_beg(*fs, ts);
	else if ((*fs)[i + 1] && (*fs)[i + 2])
	{
		(*fs)[i + 1] = 'x';
		(*fs)[i + 2] = '0';
		fl = 0;
	}
	return (fl);
}

char	*cor_pointer(char *fs, t_spec *ts)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = fs;
	if (!ft_strchr(fs, 'x'))
	{
		while (fs[i] && fs[i] != '0')
			i++;
		if (cor_pointer1(i, &fs, ts))
			ft_strdel(&tmp);
	}
	return (fs);
}

char	*handle_pointer(va_list ap, t_spec *ts)
{
	char		*fs;
	uintmax_t	i;

	i = va_arg(ap, uintmax_t);
	ts->hash = 1;
	fs = print_unsigned(ts, i, 2);
	fs = ft_lower(fs);
	fs = cor_pointer(fs, ts);
	return (fs);
}
