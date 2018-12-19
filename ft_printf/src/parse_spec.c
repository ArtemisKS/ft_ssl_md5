/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 18:08:13 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 18:08:14 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_spec(char *fmt, t_spec *ts, va_list ap)
{
	int i;

	init_struct(ts);
	i = parse_flags(fmt, ts);
	i = parse_width_bon(fmt, ts, i, ap);
	i = parse_width_bon1(fmt, ts, i, ap);
	i = parse_prec_bon(fmt, ts, i, ap);
	if (!parse_specif(fmt, ts, &i))
		i = parse_specif1(fmt, ts, i);
	return (i);
}

int		is_type(char c)
{
	int		i;
	char	*s;

	s = "psScCdDioOuUxX%";
	i = 0;
	while (s[i])
	{
		if (s[i++] == c)
			return (1);
	}
	return (0);
}

int		str_zero(char *fs)
{
	int i;

	i = 0;
	while (fs[i])
	{
		if (fs[i] == '^' && fs[i + 1] && fs[i + 1] == '@')
			write(1, "", 1);
		else if (fs[i] == '@' && !fs[i + 1])
			return (i);
		else if (fs[i] == '@' && fs[i - 1] && fs[i - 1] == '^')
			write(1, " ", 1);
		else
			write(1, &fs[i], 1);
		i++;
	}
	return (i);
}

int		output_fstring1(char *s, int fl, int j)
{
	int k;

	k = 0;
	while (s[k])
	{
		if (s[k] == '^' && s[k + 1] && s[k + 1] == '@')
		{
			fl = 1;
			j += str_zero(s);
			break ;
		}
		k++;
	}
	if (!fl)
	{
		j += ft_strlen(s);
		ft_putstr(s);
	}
	return (j);
}

int		output_fstring(va_list ap, char c, int j, t_spec *ts)
{
	char	*s;
	int		fl;

	fl = 0;
	if ((is_type(c)) || (!(is_type(c)) &&
		(ts->nil || ts->min || ts->width || ts->prec)))
	{
		s = print_format(ap, ts, c);
		if (!s)
			s = ft_strdup("(null)");
		j = output_fstring1(s, fl, j);
		fl = 0;
		ft_strdel(&s);
	}
	else
	{
		write(1, &c, 1);
		j++;
	}
	return (j);
}
