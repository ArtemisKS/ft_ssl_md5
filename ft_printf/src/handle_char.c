/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 18:01:30 by akupriia          #+#    #+#             */
/*   Updated: 2018/02/13 18:01:31 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_char(va_list ap, t_spec *ts, char c)
{
	char *fs;
	char *tmp;

	fs = ft_strnew(1);
	tmp = fs;
	if (c == 'c' && !ts->l)
	{
		fs[0] = (char)va_arg(ap, int);
		fs = print_char(ts, fs);
		ft_strdel(&tmp);
	}
	if (c == 'C' || ts->l)
		fs = handle_char_uni(ap, ts, fs);
	return (fs);
}

char	*handle_percent(t_spec *ts)
{
	char *fs;
	char *tmp;

	fs = ft_strdup("%");
	tmp = fs;
	fs = print_char(ts, fs);
	ft_strdel(&tmp);
	return (fs);
}

char	*ft_lower(char *fs)
{
	int j;

	j = 0;
	while (fs[j])
	{
		fs[j] = ft_tolower(fs[j]);
		j++;
	}
	return (fs);
}

char	*handle_unsigned1(va_list ap, t_spec *ts, char c, uintmax_t i)
{
	char *fs;

	if (ts->l)
		i = va_arg(ap, unsigned long);
	else if (ts->ll)
		i = va_arg(ap, unsigned long long);
	else if (ts->h)
		i = (unsigned short)va_arg(ap, unsigned int);
	else if (ts->hh)
		i = (unsigned char)va_arg(ap, unsigned int);
	else if (ts->z)
		i = va_arg(ap, size_t);
	else if (ts->j)
		i = va_arg(ap, uintmax_t);
	else
		i = va_arg(ap, unsigned int);
	if (c == 'u' || c == 'U')
		fs = print_unsigned(ts, i, 0);
	else if (c == 'o' || c == 'O')
		fs = print_unsigned(ts, i, 1);
	else
		fs = print_unsigned(ts, i, 2);
	return (fs);
}

char	*handle_unsigned(va_list ap, t_spec *ts, char c)
{
	char		*fs;
	uintmax_t	i;

	fs = NULL;
	i = 0;
	if (c == 'U' || c == 'O')
		ts->l = 1;
	fs = handle_unsigned1(ap, ts, c, i);
	if (c == 'x')
		fs = ft_lower(fs);
	return (fs);
}
