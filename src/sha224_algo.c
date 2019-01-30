/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 17:27:18 by akupriia          #+#    #+#             */
/*   Updated: 2019/01/31 00:49:44 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sha256.h"

uint32_t		*sha224_word(const char *word, t_md5sha *sha224)
{
	void			*message;
	uint32_t		*digest;
	size_t			len;

	sha224->buffers[A] = 0xc1059ed8;
	sha224->buffers[B] = 0x367cd507;
	sha224->buffers[C] = 0x3070dd17;
	sha224->buffers[D] = 0xf70e5939;
	sha224->buffers[E] = 0xffc00b31;
	sha224->buffers[F] = 0x68581511;
	sha224->buffers[G] = 0x64f98fa7;
	sha224->buffers[H] = 0xbefa4fa4;
	len = (uint64_t)ft_strlen(word);
	sha224->len_bytes = calc_bytenum(word, (size_t)(len + 9), 256);
	message = (unsigned char *)ft_memalloc(sha224->len_bytes);
	ft_bzero(message, sha224->len_bytes);
	ft_memcpy(message, word, len);
	sha224->len_bytes = append_pad_bits_sha(0, len, (uint32_t *)message);
	sha224->len_bits = sha224->len_bytes * CHAR_BIT;
	exec_sha256_cycle(sha224, (uint32_t *)message);
	digest = ft_memalloc(sizeof(sha224->buffers));
	ft_memcpy(digest, sha224->buffers, sizeof(sha224->buffers));
	return (digest);
}

bool			get_sha224_hash(const char *word)
{
	uint32_t	*res;
	t_md5sha	sha224;
	int			i;

	(!word) ? (puterr(2, USAGE)) : (void)1;
	ft_bzero((void *)&sha224, sizeof(sha224));
	g_ssl->info.size = 28;
	if (!(g_ssl->info.fl & FL_S))
	{
		if (!(res = hash_file_content32(word, sha224_word, &sha224)))
			return (true);
	}
	else
		res = sha224_word(word, &sha224);
	print_hash32("SHA224", res, word);
	return (false);
}
