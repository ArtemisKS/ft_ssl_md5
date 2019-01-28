/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:22:09 by akupriia          #+#    #+#             */
/*   Updated: 2019/01/28 22:43:28 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static t_oper	g_funcs[] =
{
	{"sha256", process, get_sha256_hash},
	{"sha224", process, get_sha224_hash},
	{"sha512", process, get_sha512_hash},
	{"sha384", process, get_sha384_hash},
	{"md5", process, get_md5_hash},
	{NULL, NULL, NULL},
};

static inline int		ft_strchr_ind(char *s, int c)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (-1);
}

static inline char		*find_sarg(char **av, int *i, int *k)
{
	if (av[*i][++(*k)])
		return (&av[*i][*k]);
	*k = 0;
	return (av[++(*i)]) ? (av[*i]) : (NULL);
}

int						parse_options(char **av)
{
	int			i;
	int			k;
	int			n;
	char		*data;

	i = 1;
	while ((av[++i] && !(k = 0)) && (av[i][0] == '-' && av[i][1]))
		while (av[i] && av[i][++k])
		{
			if ((n = ft_strchr_ind("pqrs", av[i][k])) == -1)
				puterr(1, USAGE, av[i][k]);
			if (av[i][k] == 'p' && (g_ssl->info.fl |= FL_S))
			{
				read_stin(STDIN_FILENO, &data) && (g_ssl->info.fl |= FL_P);
				!g_ssl->algfunc(data) && (g_ssl->info.fl &= ~FL_S);
				g_ssl->info.fl &= ~FL_P;
				free(data);
			}
			else if (av[i][k] == 'q')
				g_ssl->info.fl |= FL_Q;
			else if (av[i][k] == 'r')
				g_ssl->info.fl |= FL_R;
			else if (av[i][k] == 's' /* && (g_ssl->info.fl |= FL_DONE)*/
				&& (g_ssl->info.fl |= FL_S) &&
				!g_ssl->algfunc(find_sarg(av, &i, &k))
				&& ((g_ssl->info.fl &= ~FL_S) | 1))
				break;
		}
	return (i);
}

static bool			det_chunk_size(const char *name)
{
	if (ft_strequ(name, "sha512") || ft_strequ(name, "sha384"))
		g_chunk_sbyte = 128;
	else
		g_chunk_sbyte = 64;
	g_chunk_sbit = g_chunk_sbyte * CHAR_BIT;
	return (true);
}

void				processOpensslInput()
{
	char	*algo;
	int		i;
	char	*data;
	int		cnt;
	bool	fl;

	i = -1;
	cnt = 0;
	fl = false;
	ft_putstr("OpenSSL> ");
	while (!fl && get_next_line(STDIN_FILENO, &algo) > 0)
	{
		while (g_funcs[++i].alg_name)
		{
			if (ft_strequ(algo, g_funcs[i].alg_name)
			&& (det_chunk_size(algo)) && (g_ssl->algfunc = g_funcs[i].algo)
			&& (g_ssl->info.fl |= FL_S) && (g_ssl->info.fl |= FL_P) && ++cnt)
			{
				if (!read_stin(STDIN_FILENO, &data))
					return ;
				g_ssl->algfunc(data);
				free(data);
				fl = true;
			}
		}
		if (!fl && (i = -1))
			ft_printf("openssl:Error: '%s' is an invalid command.\n\nMessage"
			" Digest commands:\nmd5\tsha256\tsha224\nsha512\tsha384\n\n"
			"OpenSSL> ", algo);
		free(algo);
	}
	ft_printf(cnt ? "OpenSSL> %%\n" : " %%\n");
}

int					main(int ac, char **av)
{
	int	i;

	i = -1;
	g_ssl = (t_ssl *)ft_memalloc(sizeof(t_ssl));
	if (ac == 1)
		processOpensslInput();
	else
	{
		while (g_funcs[++i].alg_name)
		if (ft_strequ(av[1], g_funcs[i].alg_name)
		&& (det_chunk_size(av[1]))
		&& (g_ssl->algfunc = g_funcs[i].algo))
			return (g_funcs[i].func(ac, av));
		puterr(3, INVALID_OPTION, av[1]);
	}
	return (false);
}