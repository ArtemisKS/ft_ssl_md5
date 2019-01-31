/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 21:21:38 by akupriia          #+#    #+#             */
/*   Updated: 2019/01/31 01:43:45 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sha512.h"

uint64_t			*sha384_word(const char *word, t_sha512 *sha384)
{
	void			*message;
	uint64_t		*digest;
	uint64_t		len;

	sha384->buffers[A] = 0xcbbb9d5dc1059ed8;
	sha384->buffers[B] = 0x629a292a367cd507;
	sha384->buffers[C] = 0x9159015a3070dd17;
	sha384->buffers[D] = 0x152fecd8f70e5939;
	sha384->buffers[E] = 0x67332667ffc00b31;
	sha384->buffers[F] = 0x8eb44a8768581511;
	sha384->buffers[G] = 0xdb0c2e0d64f98fa7;
	sha384->buffers[H] = 0x47b5481dbefa4fa4;
	len = ft_strlen(word);
	sha384->len_bytes = calc_bytenum(word, (size_t)len, 512);
	message = ft_memalloc(sha384->len_bytes);
	ft_bzero(message, sha384->len_bytes);
	ft_memcpy(message, word, len);
	sha384->len_bytes = append_pad_bits_sha512(0, len, (uint64_t *)message);
	sha384->len_bits = sha384->len_bytes * CHAR_BIT;
	exec_sha512_cycle(sha384, (uint64_t *)message);
	free(message);
	digest = ft_memalloc(sizeof(sha384->buffers));
	ft_memcpy(digest, sha384->buffers, sizeof(sha384->buffers));
	return (digest);
}

bool				get_sha384_hash(const char *word)
{
	uint64_t	*res;
	t_sha512	sha384;
	int			i;

	(!word) ? (puterr(2, USAGE)) : (void)1;
	ft_bzero((void *)&sha384, sizeof(t_sha512 *));
	g_ssl->info.size = 24;
	if (!(g_ssl->info.fl & FL_S))
	{
		if (!(res = hash_file_content64(word, sha384_word, &sha384)))
			return (true);
	}
	else
		res = sha384_word(word, &sha384);
	print_hash64("SHA384", res, word);
	return (false);
}
