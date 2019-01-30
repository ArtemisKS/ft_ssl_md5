/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 21:06:47 by akupriia          #+#    #+#             */
/*   Updated: 2019/01/30 15:09:58 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sha512.h"

/*
** i[0] = i
** i[1] = s1
** i[2] = s0
** i[3] = ch
** i[4] = tmp1
** i[5] = maj
** i[6] = tmp2
** `I fucking hate you norm`
*/

static void	sha512_r_algo(uint64_t *buff, uint64_t *tmp_words)
{
	uint64_t	i[7];
	int			j;

	i[0] = -1;
	// j = -1;
	// while (++j < 8)
	// 	s[j] = 
	// ft_printf("init: \t\t %x \t %x \t %x \t %x \t %x \t %x \t %x \t %x \n\n",
	// buff[A], buff[B], buff[C], buff[D], buff[E], buff[F], buff[G], buff[H]);
	while (++(i[0]) < 80)
	{
		i[1] = EP1(buff[E]);
		i[3] = CH(buff[E],buff[F],buff[G]);
		i[4] = buff[H] + i[1] + i[3] + g_constants[i[0]] + tmp_words[i[0]];
		i[2] = EP0(buff[A]);
		i[5] = MAJ(buff[A],buff[B],buff[C]);
		i[6] = i[2] + i[5];
		buff[H] = buff[G];
		buff[G] = buff[F];
		buff[F] = buff[E];
		buff[E] = buff[D] + i[4];
		buff[D] = buff[C];
		buff[C] = buff[B];
		buff[B] = buff[A];
		buff[A] = i[4] + i[6];
		// ft_printf("comp =  %i \t %08x \t %08x \t %08x \t %08x \t %08x \t %08x \t %08x \t %08x \n",
        //         i[0], buff[A], buff[B], buff[C], buff[D], buff[E], buff[F], buff[G], buff[H]);
	}
}

static void	init_tmp_words(uint64_t *w, uint64_t *block)
{
	int			i;
	uint64_t	tmp_1;
	uint64_t	tmp_2;

	ft_memcpy(w, block, 16 * sizeof(uint64_t));
	i = -1;
	// if (ft_get_endianness())
		// while (++i < 16)
		// 	w[i] = swap_int32(w[i]);
	i = 15;
	while (++i < 80)
	{
		tmp_1 = SIG0(w[i - 15]);
		tmp_2 = SIG1(w[i - 2]);
		w[i] = w[i - 16] + tmp_1 + w[i - 7] + tmp_2;
	}
}

/*
** i[0] = i
** i[1] = j
** i[2] = nbr_block
** i[3] = extra_rounds
** `I hate you norm`
*/

static void	exec_sha512_cycle(t_sha512 *sha512, unsigned char *word)
{
	int				chunk_num;
	uint64_t		buffers[8];
	static uint64_t	tmp_words[80];
	int				i;
	int				j;

	i = -1;
	chunk_num = sha512->len_bytes / g_chunk_sbyte;
	// ft_printf("----------------------------->\nOur chunk: %d\n----------------------------->\n", chunk_num);
	ft_bzero(tmp_words, 80 * sizeof(uint64_t));
	// ft_printf("chunk_num: %d, sha512->len_bits: %d\n", chunk_num,  sha512->len_bits);
	// ft_printf("\t\t a \t\t b \t\t c \t\t d \t\t e \t\t f \t\t g \t\t h \n");
	while (++i < chunk_num && (j = -1))
	{
		ft_memcpy(buffers, sha512->buffers, sizeof(buffers));
		init_tmp_words(tmp_words, (uint64_t *)(word + i * g_chunk_sbyte));
		// ft_printf("Padded_block:\n");
		// for (int k = 0; k < sha512->len_bytes; k++)
		// 	ft_printf("%x", (word + i * g_chunk_sbyte)[k]);
		// ft_putchar('\n');
		sha512_r_algo(buffers, tmp_words);
		while (++j < 8)
			sha512->buffers[j] += buffers[j];
	}
}

uint64_t	*sha512_word(const char *word, t_sha512 *sha512)
{
	// static uint8_t	last_block[128];
	unsigned char	*message;
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
	len = (uint64_t)ft_strlen(word);
	// sha512->numBlocks = 1 + ((inp_bitlen + 16 + g_chunk_sbyte) / g_chunk_sbit);
	sha512->len_bytes = calc_bytenum(word, 512);
	message = (unsigned char *)malloc(sha512->len_bytes);
	ft_bzero(message, sha512->len_bytes);
	// message = ft_memalloc((sha512->len_bytes) * sizeof(char));
	ft_memcpy(message, word, len);

	// ft_printf("\n");
	// ft_printf("word: %s\n", word);
	// ft_printf("message: %s, sizeof(message): %d, sha.str_bits: %d, sha.byte_len: %d\n",
	// message, sizeof(message), len, sha512->len_bytes);
	sha512->len_bytes = append_pad_bits_sha512(0, len, (uint64_t *)message);
	// for (int k = 0; k < sha512->len_bytes; k++)
	// 	ft_printf("%x", (message)[k]);
	// ft_printf("\n");
	// ft_printf("sha512->len_bytes: %llu\n", sha512->len_bytes);
	sha512->len_bits = sha512->len_bytes * CHAR_BIT;
	exec_sha512_cycle(sha512, message);
	digest = ft_memalloc(sizeof(sha512->buffers));
	ft_memcpy(digest, sha512->buffers, sizeof(sha512->buffers));
	// free(message);
	return (digest);
}

static bool		print_dig32(uint32_t *digest)
{
	int			i;
	uint32_t	tmp;

	i = -1;
	while (++i < g_ssl->info.size / 4)
	{
		tmp = digest[i];
		// (g_ssl->info.swap_endian) ? tmp = swap_int32(tmp) : 1;
		ft_printf("%x", tmp);
	}
	return (true);
}

bool			get_sha512_hash(const char *word)
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
	// if (/*ft_get_endianness() && */(i = -1))
	// 	while (++i < (g_ssl->info.size / 4))
	// 		res[i] = swap_int64(res[i]);
	// ft_printh_sha512(&sha512);
	// print_dig64(res);
	// print_dig64(res);
	// ft_printf("%llx%lx%lx%lx%lx%lx%lx%lx", sha512.buffers[A], sha512.buffers[B], sha512.buffers[C],
	// 			sha512.buffers[D], sha512.buffers[E], sha512.buffers[F], sha512.buffers[G], sha512.buffers[H]);	
	print_hash64("SHA512", res, word);
	return (false);
}
