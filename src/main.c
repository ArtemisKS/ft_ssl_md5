/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:22:09 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/19 21:48:21 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static t_oper	g_funcs[] =
{
	{"sha256", process, get_sha256_hash},
	{"md5", process, get_md5_hash},
	{NULL, NULL, NULL},
};

bool					get_sha256_hash(const char *word)
{
	(void)word;
	return (false);
}

static inline int		ft_strchr_ind(char *s, int c)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (-1);
}

static inline char		*find_sarg(char *s, char **av, int *i)
{
	if (s[1])
		return (&s[1]);
	return (av[++(*i)]) ? (av[*i]) : (NULL);
}

void					parse_options(char **av)
{
	int			i;
	int			k;
	int			n;
	char 		*data;

	i = 1;
	while ((av[++i] && !(k = 0)) && (av[i][0] == '-' && av[i][1]))
		while (av[i][++k])
		{
			if ((n = ft_strchr_ind("pqrs", av[i][k])) == -1)
				puterr(1, USAGE, av[i][k]);
			if (av[i][k] == 'p' && (g_ssl->info.fl |= FL_S))
			{
				!read_stin(STDIN_FILENO, &data) && (g_ssl->info.fl |= FL_P);
				!g_ssl->algfunc(data) && (g_ssl->info.fl &= ~FL_S);
				g_ssl->info.fl &= ~FL_P;
				free(data);
			}
			else if (av[i][k] == 'q')
				g_ssl->info.fl |= FL_Q;
			else if (av[i][k] == 'r')
				g_ssl->info.fl |= FL_R;
			else if (av[i][k] == 's' && (g_ssl->info.fl |= FL_DONE))
				(g_ssl->info.fl |= FL_S) &&
				!g_ssl->algfunc(find_sarg(&av[i][k], av, &i))
				&& (g_ssl->info.fl &= ~FL_S);
		}
}

int			main(int ac, char **av)
{
	int	i;

	i = -1;
	g_ssl = (t_ssl *)ft_memalloc(sizeof(t_ssl));
	(ac == 1) ? (puterr(0, USAGE)) : (void)1; 
	while (g_funcs[++i].alg_name)
		if (ft_strequ(av[1], g_funcs[i].alg_name)
		&& (g_ssl->algfunc = g_funcs[i].algo))
			return (g_funcs[i].func(ac, av));
	return (false);
}