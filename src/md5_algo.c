/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:10:23 by akupriia          #+#    #+#             */
/*   Updated: 2019/02/02 17:10:58 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/md5.h"

static void		md5_r_algo(uint32_t *bufs, uint32_t *chunk)
{
	int			i;
	uint32_t	f;
	uint32_t	g;
	uint32_t	tmp;
	uint32_t	tmpf;

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
		f += bufs[A] + g_val[i] + chunk[g];
		tmp = bufs[A];
		bufs[A] = bufs[D];
		bufs[D] = bufs[C];
		bufs[C] = bufs[B];
		bufs[B] += ROTATE_LEFT(f, g_shift_num[i]);
	}
}

static void		exec_md5_cycle(t_md5sha *md5, uint8_t *word)
{
	int			chunk_num;
	uint32_t	buffers[4];
	int			i;
	int			j;

	i = -1;
	chunk_num = md5->len_bits / g_chunk_sbit;
	while (++i < chunk_num && (j = -1))
	{
		ft_memcpy(buffers, md5->buffers, sizeof(buffers));
		md5_r_algo(buffers, (uint32_t*)(word + i * g_chunk_sbyte));
		while (++j < 4)
			md5->buffers[j] += buffers[j];
	}
}

uint32_t		*md5_word(const char *word, t_md5sha *md5)
{
	uint8_t			*message;
	uint32_t		*digest;

	message = ft_memalloc((g_ssl->fsize + g_chunk_sbyte) * sizeof(char));
	ft_memcpy(message, word, g_ssl->fsize);
	md5->len_bytes = append_pad_bits_md5(message);
	md5->len_bits = md5->len_bytes * CHAR_BIT;
	exec_md5_cycle(md5, message);
	free(message);
	digest = ft_memalloc(sizeof(md5->buffers) / 2);
	ft_memcpy(digest, md5->buffers, sizeof(md5->buffers) / 2);
	return (digest);
}

bool			get_md5_hash(const char *word)
{
	t_md5sha	md5;
	uint32_t	*res;

	(!word) ? (puterr(2, USAGE)) : (void)1;
	ft_bzero((void *)&md5, sizeof(t_md5sha *));
	g_ssl->info.size = 16;
	g_ssl->info.swap_endian = 1;
	md5.buffers[A] = 0x67452301;
	md5.buffers[B] = 0xefcdab89;
	md5.buffers[C] = 0x98badcfe;
	md5.buffers[D] = 0x10325476;
	if (!(g_ssl->info.fl & FL_S))
	{
		if (!(res = hash_file_content32(word, md5_word, &md5)))
			return (true);
	}
	else if (!(res = md5_word(word, &md5)))
		return (true);
	print_hash32("MD5", res, word);
	g_ssl->fsize = 0;
	return (false);
}
