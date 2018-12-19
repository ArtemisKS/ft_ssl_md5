/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 18:29:58 by angavrel          #+#    #+#             */
/*   Updated: 2018/12/04 12:12:38 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# define LBITS 0x101010101010101L
# define HBITS 0x8080808080808080L
# define BUFF_SIZE 4096

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

int				ft_atoi(const char *str);
int				ft_atoi_base(const char *str, int str_base);
int				ft_isdigit(int c);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strstr(const char *str, const char *to_find);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, size_t nb);
size_t			ft_strlen(const char *str);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
void			*ft_memccpy(void *dest, const void *source, int c, size_t num);
void			*ft_memmove(void *destptr, const void *srcptr, size_t num);
int				ft_memcmp(const void *buf1, const void *buf2, size_t count);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
char			*ft_strchr(const char *str, int sym);
char			*ft_strrchr(const char *str, int sym);
char			*ft_strnstr(const char *str, const char *to_find, size_t slen);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putendl_fd(char const *s, int fd);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new_lst);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstsplit(char const *s, char c);
void			ft_swap(void *s1, void *s2);
int				ft_sqrt(int n);
int				ft_noregcmp(const char *s1, const char *s2);
size_t			ft_nbrlen(intmax_t n);
int				ft_dectooct(int n);
double			ft_power(int n, int pow);
char			*ft_itoa_base(intmax_t value, int base);
void			ft_lstpush(t_list **alst, t_list *new_lst);
char			*ft_itoa_base_u(uintmax_t value, int base);
size_t			ft_nbrlen_u(uintmax_t n);
char			*ft_strstr_start(const char *str, const char *to_find);
int				get_next_line(const int fd, char **line);
t_list			*ft_makelst(t_list *list, void const *content,
				size_t content_size);
size_t			ft_strlen(const char *str);
int				ft_strchr_index(char *s, int c);
int				ft_atoi_parse(char **s);
void			ft_bzero(void *s, size_t n);
void			*ft_memchr(const void *mem, const unsigned char c,
				size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
double			ft_pow(double n, int pow);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_wcharlen(unsigned c);
size_t			ft_wstrlen(unsigned *s);
char			*ft_strdup(const char *s1);

#endif
