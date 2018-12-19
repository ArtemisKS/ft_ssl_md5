/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 18:06:11 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 18:06:12 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_width_bon(char *fmt, t_spec *ts, int i, va_list ap)
{
	int tmp;

	if (fmt[i] == '*')
	{
		if ((tmp = va_arg(ap, int)) < 0)
		{
			ts->width = tmp * -1;
			ts->min = 1;
		}
		else
			ts->width = tmp;
		ts->asterisk1 = 1;
		i++;
	}
	else
		i += parse_width(&fmt[i], ts);
	return (i);
}

int		parse_width_bon1(char *fmt, t_spec *ts, int i, va_list ap)
{
	int tmp;

	if (fmt[i] == '*')
	{
		if ((tmp = va_arg(ap, int)) < 0)
		{
			ts->width = tmp * -1;
			ts->min = 1;
		}
		else
			ts->width = tmp;
		ts->asterisk1 = 1;
		i++;
	}
	else if (fmt[i] >= '0' && fmt[i] <= '9')
		i += parse_width(&fmt[i], ts);
	return (i);
}

int		parse_prec_bon(char *fmt, t_spec *ts, int i, va_list ap)
{
	int tmp;

	if (fmt[i] == '.')
	{
		ts->dot = 1;
		if (fmt[++i] == '*')
		{
			if ((tmp = va_arg(ap, int)) < 0)
			{
				ts->prec = tmp * -1;
				ts->min = 1;
			}
			else
				ts->prec = tmp;
			ts->asterisk2 = 1;
			i++;
		}
		else
			i += parse_pres(&fmt[i], ts);
	}
	return (i);
}

int		parse_specif(char *fmt, t_spec *ts, int *i)
{
	int fl;

	fl = 0;
	if (fmt[*i] == 'l' && fmt[*i + 1] && fmt[*i + 1] == 'l')
	{
		ts->ll = 1;
		*i += 2;
		fl = 1;
	}
	else if (fmt[*i] == 'h' && fmt[*i + 1] && fmt[*i + 1] == 'h')
	{
		ts->hh = 1;
		*i += 2;
		fl = 1;
	}
	else if (fmt[*i] == 'l')
	{
		ts->l = 1;
		(*i)++;
		fl = 1;
	}
	return (fl);
}

int		parse_specif1(char *fmt, t_spec *ts, int i)
{
	if (fmt[i] == 'h')
	{
		ts->h = 1;
		i++;
	}
	else if (fmt[i] == 'j')
	{
		ts->j = 1;
		i++;
	}
	else if (fmt[i] == 'z')
	{
		ts->z = 1;
		i++;
	}
	return (i);
}
