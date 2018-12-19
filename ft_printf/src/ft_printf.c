/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 20:51:06 by akupriia          #+#    #+#             */
/*   Updated: 2018/11/10 19:30:32 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

const char	*g_colors[] = {"{RED}", "{RESET}", "{BROWN}", "{LRED}",
	"{GREEN}", "{YELLOW}", "{BLUE}", "{MAGENTA}", "{CYAN}", "{WHITE}", NULL};
const char	*g_col[] = {"\033[31;1m", "\033[0m", "\033[22;33m",
	"\033[01;31m", "\033[32;1m", "\033[33;1m", "\033[01;34m",
	"\033[35;1m", "\033[36;1m", "\033[37;1m", NULL};

static inline int		color_func(const char **colors, char *s)
{
	int i;

	i = -1;
	while (g_colors[++i])
	{
		if (ft_strstr_start(s, colors[i]))
			break ;
	}
	return (i);
}

static inline int		check_for_colors(char *fmt, int fd)
{
	int			i;
	int			res;

	res = 0;
	i = color_func(g_colors, fmt);
	if (i < 10)
	{
		res += ft_strlen(g_colors[i]);
		write(fd, g_col[i], ft_strlen(g_col[i]));
	}
	return (res);
}

int						parse_format(int fd, va_list ap, char *fmt)
{
	int		i;
	int		j;
	t_spec	*ts;

	i = -1;
	j = 0;
	ts = (t_spec *)ft_memalloc(sizeof(t_spec));
	while (fmt[++i])
	{
		while (ft_strstr(&fmt[i], "{") && color_func(g_colors, &fmt[i]) < 10)
			i += check_for_colors(&fmt[i], fd);
		if (fmt[i] == '%' && fmt[i + 1] && ++i)
		{
			i += parse_spec(&fmt[i], ts, ap);
			j = output_fstring(ap, fmt[i], j, ts);
		}
		else if (fmt[i] && fmt[i] != '%' && ++j)
			write(fd, &fmt[i], 1);
		else if (!fmt[i])
			return (j);
	}
	ft_memdel((void**)&ts);
	return (j);
}

int						ft_printf(char *fmt, ...)
{
	va_list	ap;
	int		n;

	va_start(ap, fmt);
	n = parse_format(1, ap, fmt);
	va_end(ap);
	return (n);
}

int						ft_dprintf(int fd, char *fmt, ...)
{
	va_list	ap;
	int		n;

	va_start(ap, fmt);
	n = parse_format(fd, ap, fmt);
	va_end(ap);
	return (n);
}
