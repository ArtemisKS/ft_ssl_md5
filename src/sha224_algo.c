/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 17:27:18 by akupriia          #+#    #+#             */
/*   Updated: 2019/01/30 15:04:23 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sha256.h"


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

static void	sha224_r_algo(uint32_t *buff, uint32_t *tmp_words)
{
	uint64_t	i[7];
	int			j;

	i[0] = -1;
	// j = -1;
	// while (++j < 8)
	// 	s[j] = 
	// ft_printf("init: \t\t %x \t %x \t %x \t %x \t %x \t %x \t %x \t %x \n\n",
	// buff[A], buff[B], buff[C], buff[D], buff[E], buff[F], buff[G], buff[H]);
	while (++(i[0]) < 64)
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

static void	init_tmp_words(uint32_t *w, uint32_t *block)
{
	uint64_t	i;
	uint32_t	tmp_1;
	uint32_t	tmp_2;

	ft_memcpy(w, block, 16 * sizeof(uint32_t));
	i = -1;
	// if (ft_get_endianness())
		// while (++i < 16)
		// 	w[i] = swap_int32(w[i]);
	i = 15;
	while (++i < 64)
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

static void	exec_sha224_cycle(t_md5sha *sha224, uint32_t *word)
{
	int				chunk_num;
	uint32_t		buffers[8];
	static uint32_t	tmp_words[64];
	int				i;
	int				j;

	i = -1;
	chunk_num = sha224->len_bits / g_chunk_sbit;
	ft_bzero(tmp_words, 64 * sizeof(uint32_t));
	// ft_printf("chunk_num: %d, sha224->len_bits: %d\n", chunk_num,  sha224->len_bits);
	// ft_printf("\t\t a \t\t b \t\t c \t\t d \t\t e \t\t f \t\t g \t\t h \n");
	while (++i < chunk_num && (j = -1))
	{
		ft_memcpy(buffers, sha224->buffers, sizeof(buffers));
		init_tmp_words(tmp_words, word + i * 16);
		// ft_printf("Padded_block:\n");
		// for (int k = 0; k < 16; k++)
		// 	ft_printf("%x", (word + i * 16)[k]);
		// ft_putchar('\n');
		sha224_r_algo(buffers, tmp_words);
		while (++j < 8)
			sha224->buffers[j] += buffers[j];
	}
}

uint32_t	*sha224_word(const char *word, t_md5sha *sha224)
{
	// static uint8_t	last_block[128];
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
	len = ft_strlen(word);
	message = ft_memalloc((len + g_chunk_sbyte) * sizeof(char));
	ft_memcpy((uint32_t *)message, word, len);
	sha224->len_bytes = append_pad_bits_sha(0, len, message);
	sha224->len_bits = sha224->len_bytes * CHAR_BIT;
	exec_sha224_cycle(sha224, message);
	digest = ft_memalloc(sizeof(sha224->buffers));
	ft_memcpy(digest, sha224->buffers, sizeof(sha224->buffers));
	// free(message);
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
	// if (/*ft_get_endianness() && */(i = -1))
	// 	while (++i < (g_ssl->info.size / 4))
	// 		res[i] = swap_int32(res[i]);
	print_hash32("SHA224", res, word);
	return (false);
}
