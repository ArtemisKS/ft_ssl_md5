/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:34:32 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/19 22:14:41 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

inline void			puterr(int type, const char *strerr, ...)
{
	va_list	ap;

	va_start(ap, strerr);
	(type == 0) ? ft_printf("%s%s%s\n", RED, strerr, RESET)
	: ft_dprintf(2, "%s%s%c\n%s\n%s",  RED, "ft_ssl: illegal option -- ",
	(char)va_arg(ap, int), strerr, RESET);
	va_end(ap);
	exit(1);
}

bool				process(int ac, char **av)
{
	int32_t		i;
	char		*data;

	parse_options(av);
	if (ac == 2 && (g_ssl->info.fl & FL_Q) && !(g_ssl->info.fl & FL_DONE)
		&& (g_ssl->info.fl |= FL_DONE) && (g_ssl->info.fl |= FL_Q))
	{
		read_stin(STDIN_FILENO, &data) && (g_ssl->info.fl |= FL_S);
		!g_ssl->algfunc(data) && (g_ssl->info.fl &= ~FL_S);
		free(data);
	}
	g_ssl->info.fl &= ~FL_S;
	i = 2;
	// ft_printf("FL: %d\n", g_ssl->info.fl);
	while (av[++i])
		g_ssl->algfunc(av[i]);
	return (false);
}

bool				read_stin(int fd, char **line)
{
	int			rd;
	char		buf[BUF + 1];
	char		*cpy;

	if (fd < 0)
		return (false);
	*line = ft_strnew(1);
	while ((rd = read(fd, buf, BUF)))
	{
		if (rd == ((buf[rd] = 0) - 1))
			return (0);
		cpy = ft_strjoin(*line, buf);
		free(*line);
		*line = cpy;
	}
	return (true);
}
