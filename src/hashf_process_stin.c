/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashf_process_stin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 19:00:00 by akupriia          #+#    #+#             */
/*   Updated: 2019/01/31 00:31:56 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

uint32_t			*hash_file_content32(const char *file, t_hash32 func,
	t_md5sha *shamd)
{
	char		*content;
	uint32_t	*res;
	int			fd;

	content = NULL;
	if ((fd = open(file, O_RDONLY)) < 0
	&& ft_dprintf(STDERR_FILENO, "ft_ssl: %s: %s\n", file, strerror(errno)))
		return (NULL);
	if (!read_stin(fd, &content))
		return (NULL);
	res = func(content, shamd);
	free(content);
	return (res);
}

uint64_t			*hash_file_content64(const char *file, t_hash64 func,
	t_sha512 *sha)
{
	char		*content;
	uint64_t	*res;
	int			fd;

	content = NULL;
	if ((fd = open(file, O_RDONLY)) < 0
	&& ft_dprintf(STDERR_FILENO, "ft_ssl: %s: %s\n", file, strerror(errno)))
		return (NULL);
	if (!read_stin(fd, &content))
		return (NULL);
	res = func(content, sha);
	free(content);
	return (res);
}

inline void			puterr(int type, const char *strerr, ...)
{
	va_list	ap;

	va_start(ap, strerr);
	if (!type)
		ft_dprintf(2, "%s%s%s\n", RED, strerr, RESET);
	else if (type == 1)
		ft_dprintf(2, "%s%s%c\n%s\n%s", RED, "ft_ssl: illegal option -- ",
		(char)va_arg(ap, int), strerr, RESET);
	else if (type == 2)
		ft_dprintf(2, "%s\n%s%s%s\n", "ft_ssl: md5: option requires an"
		"argument -- s", RED, strerr, RESET);
	else
		ft_dprintf(2, "%sft_ssl: Error: '%s' is an invalid command\n%s%s\n",
		RED, va_arg(ap, char const *), RESET);
	va_end(ap);
	exit(true);
}

bool				process(int ac, char **av)
{
	int32_t		i;
	char		*data;

	i = 1;
	parse_options(av, &i);
	g_ssl->info.p_flag_used = false;
	if (i == ac - 1 && (ac == 2 || (g_ssl->info.fl & FL_Q))
	&& (g_ssl->info.fl |= FL_DONE) && (g_ssl->info.fl |= FL_P))
	{
		read_stin(STDIN_FILENO, &data) && (g_ssl->info.fl |= FL_S);
		!g_ssl->algfunc(data) && (g_ssl->info.fl &= ~FL_S);
		(g_ssl->info.fl &= ~FL_P) && (g_ssl->info.fl &= ~FL_DONE);
		free(data);
	}
	(g_ssl->info.fl & FL_S) ? g_ssl->info.fl &= ~FL_S : 1;
	while (i < ac && av[++i])
		g_ssl->algfunc(av[i]);
	return (false);
}

bool				read_stin(int fd, char **line)
{
	int			rd;
	char		buf[BUF + 1];
	char		*cpy;
	bool		fl;

	if (fd < 0)
		return (false);
	fl = false;
	if (g_ssl->info.p_flag_used)
		return (ft_strequ((*line = ft_strdup("")), ""));
	else
		*line = ft_strnew(1);
	while ((rd = read(fd, buf, BUF)))
	{
		!fl ? fl = true : 1;
		if (rd == ((buf[rd] = 0) - 1))
			return (false);
		cpy = ft_strjoin(*line, buf);
		free(*line);
		*line = cpy;
	}
	if (!fl && !rd)
		ft_memcpy(*line, "", 1);
	return (true);
}
