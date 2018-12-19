/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 18:04:23 by akupriia          #+#    #+#             */
/*   Updated: 2018/10/28 03:55:08 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*print_format(va_list ap, t_spec *ts, char c)
{
	char *res;
	char *tmp;

	if (c == 'd' || c == 'D' || c == 'i')
		res = handle_digit(ap, ts, c);
	else if (c == 'u' || c == 'U' || c == 'o'
		|| c == 'O' || c == 'X' || c == 'x')
		res = handle_unsigned(ap, ts, c);
	else if (c == 'c' || c == 'C')
		res = handle_char(ap, ts, c);
	else if (c == 's' || c == 'S')
		res = handle_string(ap, ts, c);
	else if (c == 'p')
		res = handle_pointer(ap, ts);
	else if (c == '%')
		res = handle_percent(ts);
	else
	{
		res = ft_strnew(1);
		tmp = res;
		res[0] = c;
		res = print_char(ts, res);
		ft_strdel(&tmp);
	}
	return (res);
}

void	init_struct(t_spec *ts)
{
	int i;

	i = 0;
	ts->hash = 0;
	ts->min = 0;
	ts->space = 0;
	ts->plus = 0;
	ts->nil = 0;
	ts->dot = 0;
	ts->asterisk1 = 0;
	ts->asterisk2 = 0;
	ts->hh = 0;
	ts->h = 0;
	ts->l = 0;
	ts->ll = 0;
	ts->j = 0;
	ts->z = 0;
	ts->width = 0;
	ts->prec = 0;
	ts->f_len = 0;
	ts->fl = 0;
	ts->il = 0;
	while (i < 100)
		ts->ia[i++] = 0;
	ts->len = 0;
}

int		parse_width(char *fmt, t_spec *ts)
{
	int		i;
	char	*wid;

	i = 0;
	while (fmt[i] >= '0' && fmt[i] <= '9')
		i++;
	wid = (char *)ft_memalloc(i + 1);
	i = 0;
	while (fmt[i] >= '0' && fmt[i] <= '9')
	{
		wid[i] = fmt[i];
		i++;
	}
	ts->width = ft_atoi(wid);
	ft_strdel(&wid);
	return (i);
}

int		parse_pres(char *fmt, t_spec *ts)
{
	int		i;
	char	*prec;
	int		min;
	int		res;

	min = 0;
	i = 0;
	if (fmt[i] == '-' && ++i)
		min++;
	while (fmt[i] >= '0' && fmt[i] <= '9')
		i++;
	prec = (char *)ft_memalloc(i + 1);
	i = min;
	while (fmt[i] >= '0' && fmt[i] <= '9')
	{
		prec[i - min] = fmt[i];
		i++;
	}
	res = ft_atoi(prec);
	if (min && (ts->width = res))
		ts->min = min;
	else
		ts->prec = res;
	ft_strdel(&prec);
	return (i);
}

int		parse_flags(char *fmt, t_spec *ts)
{
	int i;

	i = 0;
	while (fmt[i] == '-' || fmt[i] == '+' ||
		fmt[i] == ' ' || fmt[i] == '0' || fmt[i] == '#')
	{
		if (fmt[i] == '-')
			ts->min = 1;
		else if (fmt[i] == '+')
			ts->plus = 1;
		else if (fmt[i] == ' ')
			ts->space = 1;
		else if (fmt[i] == '0')
			ts->nil = 1;
		else if (fmt[i] == '#')
			ts->hash = 1;
		i++;
	}
	return (i);
}
