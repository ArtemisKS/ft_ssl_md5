/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:59:00 by akupriia          #+#    #+#             */
/*   Updated: 2019/02/02 13:43:54 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int					append_pad_bits_sha512(uint64_t *buf)
{
	size_t		size;
	uint64_t	inp_bitlen;
	size_t		num_blocks;
	uint		total_bits;
	int			i;

	i = -1;
	inp_bitlen = CHAR_BIT * g_ssl->fsize;
	total_bits = inp_bitlen + 16 + g_chunk_sbyte;
	num_blocks = total_bits / g_chunk_sbit;
	total_bits % g_chunk_sbit ? num_blocks++ : 1;
	((char*)buf)[g_ssl->fsize] = 0x80;
	while (++i < (num_blocks * 16) - 1)
		buf[i] = swap_int64(buf[i]);
	buf[((num_blocks * g_chunk_sbit - g_chunk_sbyte) / 64) + 1] = inp_bitlen;
	return (num_blocks * g_chunk_sbyte);
}

int					append_pad_bits_sha(uint32_t *buf)
{
	size_t		size;
	uint32_t	inp_bitlen;
	size_t		num_blocks;
	uint		total_bits;
	int			i;

	i = -1;
	inp_bitlen = CHAR_BIT * g_ssl->fsize;
	total_bits = inp_bitlen + 16 + g_chunk_sbyte;
	num_blocks = total_bits / g_chunk_sbit;
	total_bits % g_chunk_sbit ? num_blocks++ : 1;
	((char*)buf)[g_ssl->fsize] = 0x80;
	while (++i < (num_blocks * 16) - 1)
		buf[i] = swap_int32(buf[i]);
	buf[((num_blocks * g_chunk_sbit - g_chunk_sbyte) / 32) + 1] = inp_bitlen;
	return (num_blocks * g_chunk_sbyte);
}

int					append_pad_bits_md5(uint8_t *buf)
{
	size_t		size;
	uint32_t	inp_bitlen;

	size = g_ssl->fsize * CHAR_BIT;
	while (++size % g_chunk_sbit != 448)
		;
	size /= CHAR_BIT;
	buf[g_ssl->fsize] = 0x80;
	inp_bitlen = g_ssl->fsize * CHAR_BIT;
	ft_memcpy(buf + size, &inp_bitlen, 4);
	return (size + 8);
}

inline uint32_t		swap_int32(const uint32_t value)
{
	uint32_t result;

	result = 0;
	result |= (value & 0x000000FF) << 24;
	result |= (value & 0x0000FF00) << 8;
	result |= (value & 0x00FF0000) >> 8;
	result |= (value & 0xFF000000) >> 24;
	return (result);
}

inline uint64_t		swap_int64(const uint64_t val)
{
	return ((((val) & 0xff00000000000000ull) >> 56) |
			(((val) & 0x00ff000000000000ull) >> 40) |
			(((val) & 0x0000ff0000000000ull) >> 24) |
			(((val) & 0x000000ff00000000ull) >> 8) |
			(((val) & 0x00000000ff000000ull) << 8) |
			(((val) & 0x0000000000ff0000ull) << 24) |
			(((val) & 0x000000000000ff00ull) << 40) |
			(((val) & 0x00000000000000ffull) << 56));
}
