/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:22:09 by akupriia          #+#    #+#             */
/*   Updated: 2019/02/02 17:09:58 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

#define I_CMD			"is an invalid command.\n\nMessage Digest commands:\n"
#define V_CMD			"md5\tsha256\tsha224\nsha512\tsha384\n\nOpenSSL> "
#define PRINT_ERR(s)	ft_printf("openssl:Error: '%s' %s%s", s, I_CMD, V_CMD)
#define ASS_FL_S		(g_ssl->info.fl |= FL_S)
#define NASSFL_S		((g_ssl->info.fl &= ~FL_S) | 1)

#define ALGFUNC(s)		(ASS_FL_S && !g_ssl->algfunc(s) && NASSFL_S)

static t_oper			g_funcs[] =
{
	{"sha256", process, get_sha256_hash},
	{"sha224", process, get_sha224_hash},
	{"sha512", process, get_sha512_hash},
	{"sha384", process, get_sha384_hash},
	{"md5", process, get_md5_hash},
	{NULL, NULL, NULL},
};

static inline char		*find_sarg(char **av, int *i, int *k)
{
	if (av[*i][++(*k)])
		return (&av[*i][*k]);
	*k = 0;
	(av[++(*i)]) ? g_ssl->fsize = ft_strlen(av[*i]) : 1;
	return (av[*i]) ? (av[*i]) : (NULL);
}

void					parse_options(char **av, int *i)
{
	int			k;
	int			n;
	char		*data;

	while ((av[++(*i)] && !(k = 0)) && (av[(*i)][0] == '-' && av[(*i)][1]))
		while (av[*i] && av[*i][++k])
		{
			if ((n = ft_strchr_ind("pqrs", av[*i][k])) == -1)
				puterr(1, USAGE, av[*i][k]);
			if (av[*i][k] == 'p' && (g_ssl->info.fl |= FL_P))
			{
				read_stin(STDIN_FILENO, &data) && ALGFUNC(data);
				(g_ssl->info.fl & FL_P) ? g_ssl->info.fl &= ~FL_P : 1;
				g_ssl->info.p_flag_used = true;
				free(data);
			}
			else if (av[*i][k] == 'q')
				g_ssl->info.fl |= FL_Q;
			else if (av[*i][k] == 'r')
				g_ssl->info.fl |= FL_R;
			else if (av[*i][k] == 's' && ALGFUNC(find_sarg(av, i, &k)))
				break ;
		}
	(*i)--;
}

static bool				det_chunk_size(const char *name)
{
	if (ft_strequ(name, "sha512") || ft_strequ(name, "sha384"))
		g_chunk_sbyte = 128;
	else
		g_chunk_sbyte = 64;
	g_chunk_sbit = g_chunk_sbyte * CHAR_BIT;
	return (true);
}

static void				process_openssl_input(bool fl)
{
	char	*algo;
	int		i;
	char	*data;
	int		cnt;

	(i = -1) && ft_printf("OpenSSL> ");
	cnt = 0;
	while (!fl && get_next_line(STDIN_FILENO, &algo) > 0)
	{
		while (g_funcs[++i].alg_name)
			if (ft_strequ(algo, g_funcs[i].alg_name) && (det_chunk_size(algo))
			&& (g_ssl->algfunc = g_funcs[i].algo) && (g_ssl->info.fl |= FL_S)
			&& (g_ssl->info.fl |= FL_DONE) && (g_ssl->info.fl |= FL_P) && ++cnt)
			{
				if (!read_stin(STDIN_FILENO, &data))
					return ;
				g_ssl->algfunc(data);
				free(data);
				fl = true;
			}
		if (!fl && (i = -1))
			PRINT_ERR(algo);
		free(algo);
	}
	ft_printf(cnt ? "OpenSSL> %%\n" : " %%\n");
}

int						main(int ac, char **av)
{
	int	i;

	i = -1;
	g_ssl = (t_ssl *)ft_memalloc(sizeof(t_ssl));
	if (ac == 1)
		process_openssl_input(false);
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
