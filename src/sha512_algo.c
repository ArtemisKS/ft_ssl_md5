/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 21:06:47 by akupriia          #+#    #+#             */
/*   Updated: 2019/01/31 01:43:47 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sha512.h"

void		sha512_r_algo(uint64_t *buff, uint64_t *tmp_words)
{
	uint64_t	i[7];
	int			j;

	i[0] = -1;
	while (++(i[0]) < 80)
	{
		i[1] = EP1(buff[E]);
		i[3] = CH(buff[E], buff[F], buff[G]);
		i[4] = buff[H] + i[1] + i[3] + g_constants[i[0]] + tmp_words[i[0]];
		i[2] = EP0(buff[A]);
		i[5] = MAJ(buff[A], buff[B], buff[C]);
		i[6] = i[2] + i[5];
		buff[H] = buff[G];
		buff[G] = buff[F];
		buff[F] = buff[E];
		buff[E] = buff[D] + i[4];
		buff[D] = buff[C];
		buff[C] = buff[B];
		buff[B] = buff[A];
		buff[A] = i[4] + i[6];
	}
}

void		init_tmp_words512(uint64_t *w, uint64_t *block)
{
	int			i;
	uint64_t	tmp_1;
	uint64_t	tmp_2;

	ft_memcpy(w, block, 16 * sizeof(uint64_t));
	i = -1;
	i = 15;
	while (++i < 80)
	{
		tmp_1 = SIG0(w[i - 15]);
		tmp_2 = SIG1(w[i - 2]);
		w[i] = w[i - 16] + tmp_1 + w[i - 7] + tmp_2;
	}
}

void		exec_sha512_cycle(t_sha512 *sha512, uint64_t *word)
{
	int				chunk_num;
	uint64_t		buffers[8];
	static uint64_t	tmp_words[80];
	int				i;
	int				j;

	i = -1;
	chunk_num = sha512->len_bytes / g_chunk_sbyte;
	ft_bzero(tmp_words, 80 * sizeof(uint64_t));
	while (++i < chunk_num && (j = -1))
	{
		ft_memcpy(buffers, sha512->buffers, sizeof(buffers));
		init_tmp_words512(tmp_words, (uint64_t *)(word + i * g_chunk_sbyte));
		sha512_r_algo(buffers, tmp_words);
		while (++j < 8)
			sha512->buffers[j] += buffers[j];
	}
}

uint64_t	*sha512_word(const char *word, t_sha512 *sha512)
{
	void			*message;
	uint64_t		*digest;
	uint64_t		len;

	sha512->buffers[A] = 0x6a09e667f3bcc908;
	sha512->buffers[B] = 0xbb67ae8584caa73b;
	sha512->buffers[C] = 0x3c6ef372fe94f82b;
	sha512->buffers[D] = 0xa54ff53a5f1d36f1;
	sha512->buffers[E] = 0x510e527fade682d1;
	sha512->buffers[F] = 0x9b05688c2b3e6c1f;
	sha512->buffers[G] = 0x1f83d9abfb41bd6b;
	sha512->buffers[H] = 0x5be0cd19137e2179;
	len = ft_strlen(word);
	sha512->len_bytes = calc_bytenum(word, (size_t)(len + 9), 512);
	message = ft_memalloc(sha512->len_bytes);
	ft_bzero(message, sha512->len_bytes);
	ft_memcpy(message, word, len);
	sha512->len_bytes = append_pad_bits_sha512(0, len, (uint64_t *)message);
	sha512->len_bits = sha512->len_bytes * CHAR_BIT;
	exec_sha512_cycle(sha512, (uint64_t *)message);
	free(message);
	digest = ft_memalloc(sizeof(sha512->buffers));
	ft_memcpy(digest, sha512->buffers, sizeof(sha512->buffers));
	return (digest);
}

bool		get_sha512_hash(const char *word)
{
	uint64_t	*res;
	t_sha512	sha512;
	int			i;

	(!word) ? (puterr(2, USAGE)) : (void)1;
	ft_bzero((void *)&sha512, sizeof(t_sha512 *));
	g_ssl->info.size = 32;
	if (!(g_ssl->info.fl & FL_S))
	{
		if (!(res = hash_file_content64(word, sha512_word, &sha512)))
			return (true);
	}
	else
		res = sha512_word(word, &sha512);
	print_hash64("SHA512", res, word);
	return (false);
}
