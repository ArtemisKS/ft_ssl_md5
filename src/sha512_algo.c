/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 21:06:47 by akupriia          #+#    #+#             */
/*   Updated: 2019/01/15 00:06:14 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7

#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (64-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (64-(b))))

#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,28) ^ ROTRIGHT(x,34) ^ ROTRIGHT(x,39))
#define EP1(x) (ROTRIGHT(x,14) ^ ROTRIGHT(x,18) ^ ROTRIGHT(x,41))
#define SIG0(x) (ROTRIGHT(x,1) ^ ROTRIGHT(x,8) ^ ((x) >> 7))
#define SIG1(x) (ROTRIGHT(x,19) ^ ROTRIGHT(x,61) ^ ((x) >> 6))

static uint64_t const	g_constants[80] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538, 
	0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe, 
	0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab, 
	0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725, 
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 
	0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b, 
	0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218, 
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 
	0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec, 
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c, 
	0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6, 
	0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

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
	uint64_t	i;
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

static void	exec_sha512_cycle(t_sha512 *sha512, uint64_t *word)
{
	int				chunk_num;
	uint64_t		buffers[8];
	static uint64_t	tmp_words[64];
	int				i;
	int				j;

	i = -1;
	chunk_num = sha512->len_bits / g_chunk_sbit;
	ft_bzero(tmp_words, 64 * sizeof(uint64_t));
	// ft_printf("chunk_num: %d, sha512->len_bits: %d\n", chunk_num,  sha512->len_bits);
	// ft_printf("\t\t a \t\t b \t\t c \t\t d \t\t e \t\t f \t\t g \t\t h \n");
	while (++i < chunk_num && (j = -1))
	{
		ft_memcpy(buffers, sha512->buffers, sizeof(buffers));
		init_tmp_words(tmp_words, word + i * 16);
		ft_printf("Padded_block:\n");
		for (int k = 0; k < 32; k++)
			ft_printf("%x", (word + i * 16)[k]);
		ft_putchar('\n');
		sha512_r_algo(buffers, tmp_words);
		while (++j < 8)
			sha512->buffers[j] += buffers[j];
	}
}

uint64_t	*sha512_word(const char *word, t_sha512 *sha512)
{
	// static uint8_t	last_block[128];
	void			*message;
	uint64_t		*digest;
	size_t			len;

	sha512->buffers[A] = 0x6a09e667f3bcc908;
	sha512->buffers[B] = 0xbb67ae8584caa73b;
	sha512->buffers[C] = 0x3c6ef372fe94f82b;
	sha512->buffers[D] = 0xa54ff53a5f1d36f1;
	sha512->buffers[E] = 0x510e527fade682d1;
	sha512->buffers[F] = 0x9b05688c2b3e6c1f;
	sha512->buffers[G] = 0x1f83d9abfb41bd6b;
	sha512->buffers[H] = 0x5be0cd19137e2179;
	len = ft_strlen(word);
	message = ft_memalloc((len + g_chunk_sbyte) * sizeof(char));
	ft_memcpy((uint64_t *)message, word, len);
	ft_printf("word: %s\n", word);
	sha512->len_bytes = append_pad_bits_sha512(0, len, message);
	ft_printf("sha512->len_bytes: %llu\n", sha512->len_bytes);
	sha512->len_bits = sha512->len_bytes * CHAR_BIT;
	exec_sha512_cycle(sha512, message);
	digest = ft_memalloc(sizeof(sha512->buffers));
	ft_memcpy(digest, sha512->buffers, sizeof(sha512->buffers));
	// free(message);
	return (digest);
}


bool			get_sha512_hash(const char *word)
{
	uint64_t	*res;
	t_sha512	sha512;
	int			i;

	(!word) ? (puterr(2, USAGE)) : (void)1;
	ft_bzero((void *)&sha512, sizeof(sha512));
	g_ssl->info.size = 32;
	g_ssl->info.swap_endian = 1;
	if (!(g_ssl->info.fl & FL_S))
	{
		if (!(res = hash_file_content64(word, sha512_word, &sha512)))
			return (true);
	}
	else
		res = sha512_word(word, &sha512);
	if (/*ft_get_endianness() && */(i = -1))
		while (++i < (g_ssl->info.size / 4))
			res[i] = swap_int64(res[i]);
	print_hash64("SHA512", res, word);
	return (false);
}
