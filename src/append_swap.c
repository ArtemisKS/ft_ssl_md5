/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:59:00 by akupriia          #+#    #+#             */
/*   Updated: 2019/01/31 00:22:21 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int					append_pad_bits_sha512(int fsize, int slen, uint64_t *buf)
{
	size_t		size;
	uint64_t	inp_bitlen;
	size_t		num_blocks;
	int			i;

	i = -1;
	fsize += slen;
	inp_bitlen = CHAR_BIT * slen;
	num_blocks = 1 + ((inp_bitlen + 16 + g_chunk_sbyte) / g_chunk_sbit);
	((char*)buf)[slen] = 0x80;
	while (++i < (num_blocks * 16) - 1)
		buf[i] = swap_int64(buf[i]);
	buf[((num_blocks * g_chunk_sbit - g_chunk_sbyte) / 64) + 1] = inp_bitlen;
	return (num_blocks * g_chunk_sbyte);
}

int					append_pad_bits_sha(int fsize, int slen, uint32_t *buf)
{
	size_t		size;
	uint64_t	inp_bitlen;
	size_t		num_blocks;
	int			i;

	i = -1;
	fsize += slen;
	inp_bitlen = CHAR_BIT * slen;
	num_blocks = 1 + ((inp_bitlen + 16 + g_chunk_sbyte) / g_chunk_sbit);
	((char*)buf)[slen] = 0x80;
	while (++i < (num_blocks * 16) - 1)
		buf[i] = swap_int32(buf[i]);
	buf[((num_blocks * g_chunk_sbit - g_chunk_sbyte) / 32) + 1] = inp_bitlen;
	return (num_blocks * g_chunk_sbyte);
}

int					append_pad_bits_md5(int fsize, int slen, uint8_t *buf)
{
	size_t		size;
	uint32_t	inp_bitlen;

	fsize += slen;
	size = slen * CHAR_BIT;
	while (++size % g_chunk_sbit != 448)
		;
	size /= CHAR_BIT;
	buf[slen] = 0x80;
	inp_bitlen = CHAR_BIT * slen;
	ft_memcpy(buf + size, &inp_bitlen, 4);
	return (size);
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
