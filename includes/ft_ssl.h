/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:42:47 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/19 22:14:40 by akupriia         ###   ########.fr       */
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
# define INVALID_OPTION		"Error: invalid option: %s\n"
# define USAGE				"usage: ft_ssl [-pqr] [-s string] [files ...]"
# define BUF				4096

typedef bool				(*t_funcs)(int, char **);
typedef bool				(*t_algo)(const char *);

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

typedef struct				s_md5
{
	// uint32_t				words[16];
	uint32_t				buffers[4];
	uint32_t				len_bits;
	uint32_t				len_bytes;
	uint8_t					ablock[128];
}							t_md5;

typedef uint32_t*			(*t_hashalgo)(const char *, t_md5 *);

void						puterr(int type, const char *strerr, ...);
bool						read_stin(int fd, char **line);
bool						process(int ac, char **av);
void						parse_options(char **av);
bool						get_md5_hash(const char *word);


bool						get_sha256_hash(const char *word);

#endif
