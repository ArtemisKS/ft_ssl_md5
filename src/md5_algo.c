/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:10:23 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/20 22:25:08 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"
#include <stdio.h>

#define A 					0
#define B 					1
#define C 					2
#define D 					3
#define F(B, C, D) 			((B) & (C)) | (~(B) & (D))
#define G(B, C, D) 			((B) & (D)) | ((C) & ~(D))
#define H(B, C, D) 			(B) ^ (C) ^ (D)
#define I(B, C, D) 			(C) ^ (B | ~(D))
#define CHUNK_S_BYTES		64
#define MD5_STEPS_N			64
#define CHUNK_S_BITS		512
#define UINT32_BIT			(sizeof(uint32_t) * 8)
#define ROTATE_LEFT(x, n)	(((x) << (n)) | ((x) >> (32-(n))))

static const uint32_t g_val[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

static const uint32_t g_shift_num[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

// static uint32_t			leftrotate(uint32_t mess, uint32_t shift_n)
// {
// 	return ((mess << shift_n) | (mess >> ((sizeof(int32_t) * 8) - shift_n)));
// }

static void				md5_r_algo(uint32_t	*bufs, uint32_t *chunk)
{
	int			i;
	uint32_t	f;
	uint32_t	g;
	uint32_t	tmp;
	uint32_t	tmpf;
	// i = -1;
	// while (++i < 16)
	// 	md5->words[i] = ft_memcpy(md5->words[i],
	// 		chunk + i * UINT32_BIT, UINT32_BIT);
	i = -1;
	while (++i < MD5_STEPS_N)
	{
		if (i < 16 && (f = F(bufs[B], bufs[C], bufs[D])))
			g = i;
		else if (i < 32 && (f = G(bufs[B], bufs[C], bufs[D])))
			g = (i * 5 + 1) % 16;
		else if (i < 48 && (f = H(bufs[B], bufs[C], bufs[D])))
			g = (i * 3 + 5) % 16;
		else if (i < 64 && (f = I(bufs[B], bufs[C], bufs[D])))
			g = (i * 7) % 16;
		tmpf = f;
		printf("f=%x g=%d w[g]=%x\n", f, g, chunk[g]);
		f += bufs[A] + g_val[i] + chunk[g];
		tmp = bufs[A];
		bufs[A] = bufs[D];
		bufs[D] = bufs[C];
		bufs[C] = bufs[B];
		printf("rotateLeft(%x + %x + %x + %x, %d)\n", tmp, tmpf, g_val[i], chunk[g], g_shift_num[i]);
		bufs[B] += ROTATE_LEFT(f, g_shift_num[i]);
	}
}

static void		exec_md5_cycle(t_md5 *md5, uint8_t *word)
{
	// uint8_t		extra_steps;
	int			i;
	int			j;
	int			chunk_num;
	uint32_t	buffers[4];

	i = -1;
	chunk_num = md5->len_bits / CHUNK_S_BITS + 1;
	while (++i < chunk_num && (j = -1))
	{
		ft_memcpy(buffers, md5->buffers, sizeof(buffers));
		md5_r_algo(buffers, (uint32_t*)(void*)(word + i * CHUNK_S_BYTES));
		while (++j < 4)
			md5->buffers[j] += buffers[j];
	}
	// i = -1;
	// extra_steps = 1 + ((md5->len_bytes % 64) > (64 - 9));
	// while (++i < extra_steps && (j = -1))
	// {
	// 	ft_memcpy(buffers, md5->buffers, sizeof(buffers));
	// 	md5_round(buffers, (uint32_t*)(void*)(last_block + i * 64));
	// 	while (++j < 4)
	// 		md5->buffers[j] += buffers[j];
	// }
}

static int		append_pad_bits(int fsize, int slen, uint8_t *buffer)
{
	size_t		size;
	// uint32_t	bits_len;

	fsize += slen;
	// size = (slen / CHUNK_S_BYTES + 1) * CHUNK_S_BYTES;
	// (size - slen <= 8) ? size += CHUNK_S_BYTES : 1;
	// buffer[slen] = 0x80;
	// bits_len = fsize << 3;
	// ft_bzero(buffer + slen + 1, size - slen - 8 - 1);
	// // *(uint64_t*)(buffer + size - 8) = fsize << 3;
	// ft_memcpy(buffer + size, &bits_len, 4);
    for(size = slen*8 + 1; size%512!=448; size++);
    size /= 8;
    // buffer = ft_memalloc(size + 64, 1); // also appends "0" bits 
                                   // (we alloc also 64 extra bytes...)
    buffer[slen] = 128; // write the "1" bit
    uint32_t bits_len = 8*slen; // note, we append the len
    memcpy(buffer + size, &bits_len, 4);
    printf("size: %d, bits_len: %d, slen: %d\n", size, bits_len, slen);
	return (size);
}

// static void		append_pad_bits(t_md5 *md5, const char *word)
// {
// 	ft_memcpy(md5->ablock, word, sizeof(word));
// 	md5->ablock[md5->len_bits] = 1;
// }

uint32_t		*md5_word(const char *word, t_md5 *md5)
{
	// uint32_t		buffers[4];
	uint8_t			*message;
	uint32_t		*digest;
	// size_t			res_len;
	int len = ft_strlen(word);
	message = ft_memalloc((len + CHUNK_S_BYTES) * sizeof(char));
	ft_strcpy((char *)message, word);
	md5->len_bytes = append_pad_bits(0, len, message);
	md5->len_bits = md5->len_bytes * CHAR_BIT;
	// message = ft_strdup(word);
	// append_pad_bits(md5, word);
	exec_md5_cycle(md5, message);
	digest = ft_memalloc(sizeof(md5->buffers));
	ft_memcpy(digest, md5->buffers, sizeof(md5->buffers));
	// free(message);
	return (digest);
}

static uint32_t	swap_int32(const uint32_t value)
{
	uint32_t result = 0;
	result |= (value & 0x000000FF) << 24;
	result |= (value & 0x0000FF00) << 8;
	result |= (value & 0x00FF0000) >> 8;
	result |= (value & 0xFF000000) >> 24;
	return result;
}

static void		print_digest(uint32_t *digest)
{
	uint32_t	i;
	uint32_t	tmp;

	i = -1;
	while (++i < g_ssl->info.size / 4)
	{
		tmp = digest[i];
		(g_ssl->info.swap_endian) ? tmp = swap_int32(tmp) : 1;
		ft_printf("%8.8x", tmp);
	}
	ft_putchar('\n');
}

uint32_t	*hash_file_content(const char *word, t_hashalgo func)
{
	uint32_t	*res;

	res = NULL;
	(void)word;
	(void)func;
	return (res);
}

bool			get_md5_hash(const char *word)
{
	t_md5		md5;
	uint32_t	*res;

	ft_bzero((void *)&md5, sizeof(md5));
	g_ssl->info.size = 16;
	g_ssl->info.swap_endian = 1;
	md5.buffers[A] = 0x67452301;
	md5.buffers[B] = 0xefcdab89;
	md5.buffers[C] = 0x98badcfe;
	md5.buffers[D] = 0x10325476;
	if (!(g_ssl->info.fl & FL_S))
	{
		if (!(res = hash_file_content(word, md5_word)))
			return (true);
	}
	else if (!(res = md5_word(word, &md5)))
		return (true);
	print_digest(res);
	return (false);
}
