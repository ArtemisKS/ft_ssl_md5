/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_nil_sth.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:55:38 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 17:55:39 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*char_nominnil_prec(t_spec *ts, char *s, char *fs, int j)
{
	int j1;

	j1 = 0;
	if (ts->width)
	{
		if (s[0])
		{
			if (!s[1])
				while (j < ts->f_len - (int)ts->prec)
					fs[j++] = ' ';
			else
				while (j < ts->f_len - (int)ft_strlen(s))
					fs[j++] = ' ';
		}
	}
	if (s[0])
		while (j < ts->f_len && j1 < (int)ft_strlen(s))
			fs[j++] = s[j1++];
	else
	{
		fs[j++] = '^';
		fs[j] = '@';
	}
	return (fs);
}

char	*char_nominnil_noprec(char *s, char *fs, int j, t_spec *ts)
{
	int j1;

	j1 = 0;
	while (j < ts->f_len - ts->len)
		fs[j++] = ' ';
	if (s[0])
		while (j < ts->f_len && j1 < (int)ft_strlen(s))
			fs[j++] = s[j1++];
	else
	{
		fs[j++] = '^';
		fs[j] = '@';
	}
	return (fs);
}

char	*handle_char_nominnil(t_spec *ts, char *s, char *fs)
{
	int j;

	j = 0;
	if (ts->prec)
		fs = char_nominnil_prec(ts, s, fs, j);
	else
		fs = char_nominnil_noprec(s, fs, j, ts);
	return (fs);
}

int		char_nil_precwidth(t_spec *ts, char *s, char **fs)
{
	int j;

	j = 0;
	if (s[0])
	{
		if (!s[1])
			while (j < ts->f_len - (int)ts->prec)
				(*fs)[j++] = '0';
		else
			while (j < ts->f_len - (int)ft_strlen(s))
				(*fs)[j++] = '0';
	}
	return (j);
}

char	*char_nil_noprec(char *s, char *fs, t_spec *ts)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	while (j < ts->f_len - ts->len)
		fs[j++] = '0';
	if (s[0])
		while (j < ts->f_len && j1 < (int)ft_strlen(s))
			fs[j++] = s[j1++];
	else
	{
		fs[j++] = '^';
		fs[j] = '@';
	}
	return (fs);
}
