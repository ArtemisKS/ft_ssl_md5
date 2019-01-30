/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:34:32 by akupriia          #+#    #+#             */
/*   Updated: 2019/01/30 15:18:38 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static bool		print_dig32(uint32_t *digest)
{
	int			i;
	uint32_t	tmp;

	i = -1;
	while (++i < g_ssl->info.size / 4)
	{
		tmp = digest[i];
		(g_ssl->info.swap_endian) ? tmp = swap_int32(tmp) : 1;
		ft_printf("%8.8x", tmp);
	}
	return (true);
}


static bool		print_dig64(uint64_t *digest)
{
	int			i;
	uint64_t	tmp;

	i = -1;
	while (++i < g_ssl->info.size / 4)
	{
		tmp = digest[i];
		ft_printf("%16.16lx", tmp);
	}
	return (true);
}

void		print_hash32(char const *halgo, uint32_t *digest, char const *word)
{
	// ft_printf("g_ssl->info.fl: %d\n", g_ssl->info.fl);
	if (g_ssl->info.fl & FL_P && g_ssl->info.fl & FL_DONE)
		print_dig32(digest);
	else if (g_ssl->info.fl & FL_P)
		(ft_printf("%s", word) | 1) && print_dig32(digest);
	else if (g_ssl->info.fl & FL_Q)
		print_dig32(digest);
	else if (g_ssl->info.fl & FL_R)
		print_dig32(digest) && (g_ssl->info.fl & FL_S ? ft_printf(" \"%s\"", word)
		: ft_printf(" %s", word));
	else
	{
		g_ssl->info.fl & FL_S ? ft_printf("%s (\"%s\") = ", halgo, word)
		: ft_printf("%s (%s) = ", halgo, word);
		print_dig32(digest);
	}
	ft_putchar('\n');
	free(digest);
}

void		print_hash64(char const *halgo, uint64_t *digest, char const *word)
{
	// ft_printf("g_ssl->info.fl: %d\n", g_ssl->info.fl);
	if (g_ssl->info.fl & FL_P && g_ssl->info.fl & FL_DONE)
		print_dig64(digest);
	else if (g_ssl->info.fl & FL_P)
		(ft_printf("%s", word) | 1) && print_dig64(digest);
	else if (g_ssl->info.fl & FL_Q)
		print_dig64(digest);
	else if (g_ssl->info.fl & FL_R)
		print_dig64(digest) && (g_ssl->info.fl & FL_S ? ft_printf(" \"%s\"", word)
		: ft_printf(" %s", word));
	else
	{
		g_ssl->info.fl & FL_S ? ft_printf("%s (\"%s\") = ", halgo, word)
		: ft_printf("%s (%s) = ", halgo, word);
		print_dig64(digest);
	}
	ft_putchar('\n');
	free(digest);
}

uint32_t	*hash_file_content32(const char *word, t_hash32 func, t_md5sha *shamd)
{
	char		*content;
	uint32_t	*res;
	int			fd;

	content = NULL;
	if ((fd = open(word, O_RDONLY)) < 0
	&& ft_dprintf(STDERR_FILENO, "ft_ssl: %s: %s\n", word, strerror(errno)))
		return (NULL);
	if (!read_stin(fd, &content))
		return (NULL);
	res = func(content, shamd);
	free(content);
	return (res);
}

uint64_t	*hash_file_content64(const char *word, t_hash64 func, t_sha512 *sha)
{
	char		*content;
	uint64_t	*res;
	int			fd;

	content = NULL;
	if ((fd = open(word, O_RDONLY)) < 0
	&& ft_dprintf(STDERR_FILENO, "ft_ssl: %s: %s\n", word, strerror(errno)))
		return (NULL);
	if (!read_stin(fd, &content))
		return (NULL);
	res = func(content, sha);
	free(content);
	return (res);
}

size_t			calc_bytenum(const char *str, int algo)
{
	size_t			len;

	len = ft_strlen(str) + 9;
	if (algo == 256)
	{
		while (len * 8 % 512 != 0)
			len++;
	}
	else if (algo == 512)
	{
		len += 8;
		while (len * 8 % 1024 != 0)
			len++;
	}
	return (len);
}


int					append_pad_bits_sha512(int fsize, int slen, uint64_t *buf)
{
	size_t		size;
    __uint128_t	inp_bitlen = CHAR_BIT * slen;
	size_t		numBlocks = 1 + ((inp_bitlen + 16 + g_chunk_sbyte) / g_chunk_sbit);

	fsize += slen;
	// ft_printf("g_chunk_sbyte: %d; paddedInput:\n", g_chunk_sbyte);
	// for (int k = 0; k < ((numBlocks * 1024 - 128) / 64) + 2; k++)
	// 	ft_printf("%x", buf[k]);
    // ft_printf("\n");
    ((char*)buf)[slen] = 0x80;
	// for(uint i = 0; i < (numBlocks * 16) - 1; i++)
    //     buf[i] = swap_int64(buf[i]);
	for(uint i = 0; i < (numBlocks * 16) - 1; i++)
        buf[i] = swap_int64(buf[i]);
	buf[((numBlocks * g_chunk_sbit - g_chunk_sbyte) / 64) + 1] = inp_bitlen;
	// ft_printf("g_chunk_sbyte: %d; paddedInput:\n", g_chunk_sbyte);
	// buf[((numBlocks * g_chunk_sbit - g_chunk_sbyte) / 64) + 1] = inp_bitlen;
	// ft_printf("g_chunk_sbyte: %d; paddedInput:\n", g_chunk_sbyte);
	// for (int k = 0; k < ((numBlocks * g_chunk_sbit - g_chunk_sbyte) / 32) + 2; k++)
	// 	ft_printf("%x", buf[k]);
    // ft_printf("\n");
	return (numBlocks * g_chunk_sbyte);
}

int					append_pad_bits_sha(int fsize, int slen, uint32_t *buf)
{
	size_t		size;
    uint64_t	inp_bitlen = CHAR_BIT * slen; // note, we append the len
	// uint32_t	inp_bitlen;
	size_t numBlocks = 1 + ((inp_bitlen + 16 + g_chunk_sbyte) / g_chunk_sbit);

	fsize += slen;
	// size = (slen / g_chunk_sbyte + 1) * g_chunk_sbyte;
	// (size - slen <= 8) ? size += g_chunk_sbyte : 1;
	// buf[slen] = 0x80;
	// inp_bitlen = fsize << 3;
	// ft_bzero(buf + slen + 1, size - slen - 8 - 1);
	// // *(uint64_t*)(buf + size - 8) = fsize << 3;
	// ft_memcpy(buf + size, &inp_bitlen, 4);
    // for(size = slen*CHAR_BIT + 1; size % g_chunk_sbit != 448; size++);
    // size /= CHAR_BIT;
    // buf = ft_memalloc(size + 64, 1); // also appends "0" bits 
                                   // (we alloc also 64 extra bytes...)
    ((char*)buf)[slen] = 0x80; // write the "1" bit
	for(uint i = 0; i < (numBlocks * 16) - 1; i++)
        buf[i] = swap_int32(buf[i]);
	buf[((numBlocks * g_chunk_sbit - g_chunk_sbyte) / 32) + 1] = inp_bitlen;
	// ft_memcpy(((char*)buf + size), &inp_bitlen, 4);
    // printf("size: %d, inp_bitlen: %d, slen: %d\n", size, inp_bitlen, slen);
	// ft_printf("paddedInput:\n");
	// for (int k = 0; k < ((numBlocks * 512 - 64) / 32) + 2; k++)
	// 	ft_printf("%x", buf[k]);
    // ft_printf("\n");
	// ft_printf("g_chunk_sbyte: %d; paddedInput:\n", g_chunk_sbyte);
	// buf[((numBlocks * g_chunk_sbit - g_chunk_sbyte) / 64) + 1] = inp_bitlen;
	// ft_printf("g_chunk_sbyte: %d; paddedInput:\n", g_chunk_sbyte);
	// for (int k = 0; k < ((numBlocks * g_chunk_sbit - g_chunk_sbyte) / 32) + 2; k++)
	// 	ft_printf("%x", buf[k]);
    // ft_printf("\n");
	return (numBlocks * g_chunk_sbyte);
}

int					append_pad_bits_md5(int fsize, int slen, uint8_t *buf)
{
	size_t		size;
	// uint32_t	inp_bitlen;

	fsize += slen;
	// size = (slen / g_chunk_sbyte + 1) * g_chunk_sbyte;
	// (size - slen <= 8) ? size += g_chunk_sbyte : 1;
	// buf[slen] = 0x80;
	// inp_bitlen = fsize << 3;
	// ft_bzero(buf + slen + 1, size - slen - 8 - 1);
	// // *(uint64_t*)(buf + size - 8) = fsize << 3;
	// ft_memcpy(buf + size, &inp_bitlen, 4);
    for(size = slen*CHAR_BIT + 1; size % g_chunk_sbit != 448; size++);
    size /= CHAR_BIT;
    // buf = ft_memalloc(size + 64, 1); // also appends "0" bits 
                                   // (we alloc also 64 extra bytes...)
    buf[slen] = 0x80; // write the "1" bit
    uint32_t inp_bitlen = CHAR_BIT*slen; // note, we append the len
    ft_memcpy(buf + size, &inp_bitlen, 4);
    // printf("size: %d, inp_bitlen: %d, slen: %d\n", size, inp_bitlen, slen);
	return (size);
}

inline uint32_t		swap_int32(const uint32_t value)
{
	uint32_t result = 0;
	result |= (value & 0x000000FF) << 24;
	result |= (value & 0x0000FF00) << 8;
	result |= (value & 0x00FF0000) >> 8;
	result |= (value & 0xFF000000) >> 24;
	return result;
}

inline uint64_t 	swap_int64(const uint64_t val)
{
	return ((((val) & 0xff00000000000000ull) >> 56) |
			(((val) & 0x00ff000000000000ull) >> 40) |
			(((val) & 0x0000ff0000000000ull) >> 24) |
			(((val) & 0x000000ff00000000ull) >> 8 ) |
			(((val) & 0x00000000ff000000ull) << 8 ) |
			(((val) & 0x0000000000ff0000ull) << 24) |
			(((val) & 0x000000000000ff00ull) << 40) |
			(((val) & 0x00000000000000ffull) << 56));
}

inline void			puterr(int type, const char *strerr, ...)
{
	va_list	ap;

	va_start(ap, strerr);
	if (!type)
		ft_dprintf(2, "%s%s%s\n", RED, strerr, RESET);
	else if (type == 1)
		ft_dprintf(2, "%s%s%c\n%s\n%s",  RED, "ft_ssl: illegal option -- ",
		(char)va_arg(ap, int), strerr, RESET);
	else if (type == 2)
		ft_dprintf(2, "%s\n%s%s%s\n", "ft_ssl: md5: option requires an"
		"argument -- s", RED, strerr, RESET);
	else
		ft_dprintf(2, "%sft_ssl: Error: '%s' is an invalid command\n%s%s\n",
		RED, va_arg(ap, char const *), RESET);
	va_end(ap);
	exit(true);
}

bool				process(int ac, char **av)
{
	int32_t		i;
	char		*data;

	i = parse_options(av) - 1;
	g_ssl->info.p_flag_used = false;
	if (i == ac - 1 && (ac == 2 || ((g_ssl->info.fl & FL_Q) /*&& !(g_ssl->info.fl & FL_DONE)*/))
		/*&& (g_ssl->info.fl |= FL_DONE)*/ /*&& (g_ssl->info.fl |= FL_Q)*/)
	{
		read_stin(STDIN_FILENO, &data) && (g_ssl->info.fl |= FL_S);
		!g_ssl->algfunc(data) && (g_ssl->info.fl &= ~FL_S);
		free(data);
	}
	g_ssl->info.fl &= ~FL_S;
	// ft_printf("FL: %d\n", g_ssl->info.fl);
	while (i < ac && av[++i])
		g_ssl->algfunc(av[i]);
	return (false);
}

bool				read_stin(int fd, char **line)
{
	int			rd;
	char		buf[BUF + 1];
	char		*cpy;
	bool		fl;

	if (fd < 0)
		return (false);
	fl = false;
	// write(1, "wtf111\n", 7);
	if (g_ssl->info.p_flag_used)
	{
		*line = ft_strdup("");
		return (true);
	}
	else
		*line = ft_strnew(1);
	while ((rd = read(fd, buf, BUF)) && (fl = true))
	{
		if (rd == ((buf[rd] = 0) - 1))
			return (false);
		cpy = ft_strjoin(*line, buf);
		free(*line);
		*line = cpy;
	}
	// write(1, "wtf111\n", 7);
	if (!fl && !rd)
		ft_memcpy(*line, "", 1);
	// ft_printf("our str: '%s'\n", *line);
	return (true);
}
