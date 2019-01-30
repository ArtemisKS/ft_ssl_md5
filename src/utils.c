/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:34:32 by akupriia          #+#    #+#             */
/*   Updated: 2019/01/31 00:57:29 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static bool	print_dig32(uint32_t *digest)
{
	int			i;
	uint32_t	tmp;

	i = -1;
	while (++i < g_ssl->info.size / 4)
	{
		tmp = digest[i];
		(g_ssl->info.swap_endian) ? tmp = swap_int32(tmp) : 1;
		ft_printf("%8.8x", tmp);
	}
	return (true);
}

static bool	print_dig64(uint64_t *digest)
{
	int			i;
	uint64_t	tmp;

	i = -1;
	while (++i < g_ssl->info.size / 4)
	{
		tmp = digest[i];
		ft_printf("%16.16lx", tmp);
	}
	return (true);
}

void		print_hash32(char const *halgo, uint32_t *digest,
	char const *word)
{
	if (g_ssl->info.fl & FL_P && g_ssl->info.fl & FL_DONE)
		print_dig32(digest);
	else if (g_ssl->info.fl & FL_P)
		(ft_printf("%s", word) | 1) && print_dig32(digest);
	else if (g_ssl->info.fl & FL_Q)
		print_dig32(digest);
	else if (g_ssl->info.fl & FL_R)
		print_dig32(digest) && (g_ssl->info.fl & FL_S ?
		ft_printf(" \"%s\"", word) : ft_printf(" %s", word));
	else
	{
		g_ssl->info.fl & FL_S ? ft_printf("%s (\"%s\") = ", halgo, word)
		: ft_printf("%s (%s) = ", halgo, word);
		print_dig32(digest);
	}
	ft_putchar('\n');
	free(digest);
}

void		print_hash64(char const *halgo, uint64_t *digest, char const *word)
{
	if (g_ssl->info.fl & FL_P && g_ssl->info.fl & FL_DONE)
		print_dig64(digest);
	else if (g_ssl->info.fl & FL_P)
		(ft_printf("%s", word) | 1) && print_dig64(digest);
	else if (g_ssl->info.fl & FL_Q)
		print_dig64(digest);
	else if (g_ssl->info.fl & FL_R)
		print_dig64(digest) && (g_ssl->info.fl & FL_S ?
		ft_printf(" \"%s\"", word) : ft_printf(" %s", word));
	else
	{
		g_ssl->info.fl & FL_S ? ft_printf("%s (\"%s\") = ", halgo, word)
		: ft_printf("%s (%s) = ", halgo, word);
		print_dig64(digest);
	}
	ft_putchar('\n');
	free(digest);
}

size_t		calc_bytenum(const char *str, size_t slen, int algo)
{
	if (algo == g_chunk_sbit / 2)
		while (slen * CHAR_BIT % g_chunk_sbit)
			slen++;
	else if (algo == g_chunk_sbit / 2 && (slen += CHAR_BIT))
		while (slen * CHAR_BIT % g_chunk_sbit)
			slen++;
	return (slen);
}
