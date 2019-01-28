/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:42:47 by akupriia          #+#    #+#             */
/*   Updated: 2019/01/28 20:55:32 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include <libftprintf.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
# include <stdarg.h>

# define RESET				"\033[0m"
# define B_CYAN				"\033[1;36m"
# define B_YELLOW			"\033[1;33m"
# define BLUE				"\033[0;34m"
# define YELLOW				"\033[0;33m"
# define GREEN				"\033[0;32m"
# define PURPLE				"\033[0;35m"
# define RED				"\033[0;31m"
# define INVALID_OPTION		"ft_ssl: Error: '%s' is an invalid command:\n"
# define USAGE				"usage: ft_ssl [md5] [-pqr] [-s string] [files ...]"
# define BUF				4096
// # define CHUNK_S_BYTES		64
// # define CHUNK_S_BYTES_512	128
# define MD5_STEPS_N		64
// # define CHUNK_S_BITS		512
// # define CHUNK_S_BITS_512	1024

typedef bool				(*t_funcs)(int, char **);
typedef bool				(*t_algo)(const char *);
size_t						g_chunk_sbyte;
size_t						g_chunk_sbit;

enum FLAGS
{
	FL_P = 		1,
	FL_Q = 		2,
	FL_R = 		4,
	FL_S = 		8,
	FL_DONE = 	16
};

typedef struct				s_info
{
	uint8_t					fl;
	uint8_t					swap_endian;
	uint32_t				size;
}							t_info;

typedef struct				s_oper
{
	const char				*alg_name;
	t_funcs					func;
	t_algo					algo;
}							t_oper;

typedef struct				s_ssl
{
	t_info					info;
	t_oper					oper;
	t_algo					algfunc;
}							t_ssl;

t_ssl						*g_ssl;

typedef struct				s_md5sha
{
	// uint32_t				words[16];
	uint32_t				buffers[8];
	uint32_t				len_bits;
	uint32_t				len_bytes;
}							t_md5sha;

typedef struct				s_sha512
{
	// uint32_t				words[16];
	uint64_t				buffers[8];
	uint64_t				len_bits;
	uint64_t				len_bytes;
	uint					numBlocks;
}							t_sha512;

typedef uint32_t*			(*t_hash32)(const char *, t_md5sha *);
typedef uint64_t*			(*t_hash64)(const char *, t_sha512 *);

void						puterr(int type, const char *strerr, ...);
bool						read_stin(int fd, char **line);
bool						process(int ac, char **av);
int							parse_options(char **av);
bool						get_md5_hash(const char *word);
uint32_t					swap_int32(const uint32_t value);
uint64_t					swap_int64(const uint64_t value);
int							append_pad_bits_sha(int fsize, int slen, uint32_t *buf);
int							append_pad_bits_sha512(int fsize, int slen, uint64_t *buf);
int							append_pad_bits_md5(int fsize, int slen, uint8_t *buf);
uint32_t					*hash_file_content32(const char *word, t_hash32 func, t_md5sha *shamd);
uint64_t					*hash_file_content64(const char *word, t_hash64 func, t_sha512 *sha);
bool						get_sha256_hash(const char *word);
void						print_hash32(char const *alg, uint32_t *digest, char const *word);
void						print_hash64(char const *alg, uint64_t *digest, char const *word);
bool						get_sha224_hash(const char *word);
bool						get_sha256_hash(const char *word);
bool						get_sha512_hash(const char *word);
bool						get_sha384_hash(const char *word);

#endif
