/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knikanor <knikanor@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 18:00:09 by akupriia          #+#    #+#             */
/*   Updated: 2018/10/28 02:11:41 by knikanor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_uni	*init_uni(t_uni *tu)
{
	tu->mask1 = 0;
	tu->mask2 = 0;
	tu->mask3 = 0;
	tu->o1 = 0;
	tu->o2 = 0;
	tu->o3 = 0;
	tu->o4 = 0;
	return (tu);
}

char	*print_unicode(int value, t_spec *ts, int i)
{
	t_uni		*tu;
	int			size;
	char		*res;

	tu = (t_uni *)ft_memalloc(sizeof(t_uni));
	tu = init_uni(tu);
	tu->mask1 = 49280;
	tu->mask2 = 14712960;
	tu->mask3 = 4034953344;
	size = size_bin(value);
	if (size <= 7)
		res = print_uni_7(value, ts, i);
	else if (size <= 11)
		res = print_uni_11(value, ts, i, tu);
	else if (size <= 16)
		res = print_uni_16(value, ts, i, tu);
	else
		res = print_uni_21(value, ts, i, tu);
	ft_memdel((void**)&tu);
	return (res);
}

char	*handle_string_uni(va_list ap, t_spec *ts, char *s)
{
	wchar_t		*wa;
	char		*s1;
	char		*tmp;
	int			i;

	wa = va_arg(ap, wchar_t *);
	i = 0;
	if (wa)
	{
		while (wa[i])
		{
			tmp = s;
			s1 = print_unicode(wa[i], ts, i);
			s = ft_strjoin(s, s1);
			ft_strdel(&s1);
			ft_strdel(&tmp);
			i++;
		}
		tmp = s;
		s = handle_str(ts, s, 'S');
		ft_strdel(&tmp);
	}
	else
		ft_strdel(&s);
	return (s);
}

char	*handle_string(va_list ap, t_spec *ts, char c)
{
	char *s;

	s = (char *)ft_strnew(1);
	if (c == 's' && !ts->l)
	{
		ft_strdel(&s);
		s = va_arg(ap, char *);
	}
	if (c == 'S' || ts->l)
		s = handle_string_uni(ap, ts, s);
	if (!s && !ts->nil && !ts->min)
		return (s);
	if (c == 's')
		s = handle_str(ts, s, 's');
	return (s);
}

char	*handle_char_uni(va_list ap, t_spec *ts, char *fs)
{
	int		value;
	char	*tmp;
	int		i;

	value = va_arg(ap, int);
	i = 0;
	tmp = fs;
	fs = print_unicode(value, ts, i);
	ft_strdel(&tmp);
	if (!fs[0])
	{
		ft_strdel(&fs);
		fs = ft_strdup("^@");
	}
	tmp = fs;
	fs = print_char(ts, fs);
	ft_strdel(&tmp);
	return (fs);
}
