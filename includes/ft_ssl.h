/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:42:47 by akupriia          #+#    #+#             */
/*   Updated: 2019/02/02 17:23:29 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <libftprintf.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
# include <stdarg.h>
# include <sys/stat.h>

# define RESET				"\033[0m"
# define B_CYAN				"\033[1;36m"
# define B_YELLOW			"\033[1;33m"
# define BLUE				"\033[0;34m"
# define YELLOW				"\033[0;33m"
# define GREEN				"\033[0;32m"
# define PURPLE				"\033[0;35m"
# define RED				"\033[0;31m"
# define INVALID_OPTION		"ft_ssl: Error: '%s' is an invalid command:\n"
# define PROGRAM			"usage: ft_ssl [md5 | sha[224 | 256 | 384 | 512]]"
# define USAGE				PROGRAM " [-pqr] [-s string] [files ...]"
# define BUF				100000000
# define MD5_STEPS_N		64

typedef bool				(*t_funcs)(int, char **);
typedef bool				(*t_algo)(const char *);
typedef struct stat			t_stat;
size_t						g_chunk_sbyte;
size_t						g_chunk_sbit;

enum						e_flags
{
	FL_P = 1,
	FL_Q = 2,
	FL_R = 4,
	FL_S = 8,
	FL_DONE = 16
};

typedef struct				s_info
{
	uint8_t					fl;
	uint8_t					swap_endian;
	uint32_t				size;
	bool					p_flag_used;
}							t_info;

typedef struct				s_oper
{
	const char				*alg_name;
	t_funcs					func;
	t_algo					algo;
}							t_oper;

typedef struct				s_ssl
{
	uint					fsize;
	t_info					info;
	t_oper					oper;
	t_algo					algfunc;
	bool					is_dir;
}							t_ssl;

t_ssl						*g_ssl;

typedef struct				s_md5sha
{
	uint32_t				buffers[8];
	uint32_t				len_bits;
	uint32_t				len_bytes;
}							t_md5sha;

typedef struct				s_sha512
{
	uint64_t				buffers[8];
	uint64_t				len_bits;
	uint64_t				len_bytes;
	uint					num_blocks;
}							t_sha512;

typedef uint64_t*			(*t_hash64)(const char *, t_sha512 *);
uint64_t					*hash_file_content64(const char *word,
	t_hash64 func, t_sha512 *sha);

typedef uint32_t*			(*t_hash32)(const char *, t_md5sha *);
uint32_t					*hash_file_content32(const char *word,
	t_hash32 func, t_md5sha *shamd);

void						puterr(int type, const char *strerr, ...);
bool						read_stin(int fd, char **line);
bool						process(int ac, char **av);
void						parse_options(char **av, int *i);
bool						get_md5_hash(const char *word);
uint32_t					swap_int32(const uint32_t value);
uint64_t					swap_int64(const uint64_t value);
int							append_pad_bits_sha(uint32_t *buf);
int							append_pad_bits_sha512(uint64_t *buf);
int							append_pad_bits_md5(uint8_t *buf);
bool						get_sha256_hash(const char *word);
void						print_hash32(char const *alg, uint32_t *digest,
	char const *word);
void						print_hash64(char const *alg, uint64_t *digest,
	char const *word);
bool						get_sha224_hash(const char *word);
bool						get_sha256_hash(const char *word);
bool						get_sha512_hash(const char *word);
bool						get_sha384_hash(const char *word);
size_t						calc_bytenum(const char *str, size_t len, int alg);
void						sha512_r_algo(uint64_t *buff, uint64_t *tmp_words);
void						exec_sha512_cycle(t_sha512 *sha512, uint8_t *w);
void						sha256_r_algo(uint32_t *buff, uint32_t *tmp_words);
void						exec_sha256_cycle(t_md5sha *sha256, uint32_t *word);

#endif
