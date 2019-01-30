# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/04 12:03:18 by akupriia          #+#    #+#              #
#    Updated: 2019/01/30 19:50:52 by akupriia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

SRC :=	ft_putchar.c \
		ft_atoi.c \
		ft_strstr.c \
		ft_strcat.c \
		ft_strncat.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_memalloc.c \
		ft_memdel.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_strclr.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strsplit.c \
		ft_itoa.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstsplit.c \
		ft_swap.c \
		ft_sqrt.c \
		ft_noregcmp.c \
		ft_nbrlen.c \
		ft_dectooct.c \
		ft_power.c \
		ft_itoa_base.c \
		ft_putendl.c \
		ft_putnbr.c \
		ft_putstr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdup.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_lstpush.c \
		ft_atoi_base.c \
		ft_strstr_start.c \
		get_next_line.c \
		ft_itoa_base_u.c \
		ft_nbrlen_u.c \
		ft_atoi_parse.c \
		ft_pow.c \
		ft_wcharlen.c \
		ft_strchr_index.c \
		ft_wstrlen.c \
		ft_lstpush.c \
		ft_atoi_base.c \
		ft_strstr_start.c \
		get_next_line.c \
		ft_strchr_ind.c

NAME :=		libft.a
HFILES :=	libft.h

CC :=		clang
CFLAGS :=	-Wall -Wextra -Werror

OBJ_D :=	.obj/
OBJS :=		$(addprefix $(OBJ_D), $(SRC:%.c=%.o))


all: $(NAME)

$(NAME): $(OBJ_D) $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
$(OBJ_D):
	mkdir -p $(OBJ_D)
$(OBJ_D)%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_D)
fclean: clean
	rm -f $(NAME)
re: fclean all