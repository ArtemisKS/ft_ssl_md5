# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/18 11:15:08 by akupriia          #+#    #+#              #
#    Updated: 2019/01/30 19:03:18 by akupriia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME	:=	ft_ssl
LIB		:=	ft_printf/
LIB_HDR	:=	$(LIB)hdr/
SRC_D	:=	src/
OBJ_D	:=	.obj/

# -Wall -Wextra -Werror
CFLAGS	:=	 -g
IFLAGS	:=	-I $(LIB_HDR) -I ./
LFLAGS	:=	-lftprintf -L $(LIB)
CC		:=	clang

SRC		:=	md5_algo sha256_algo sha224_algo sha512_algo sha384_algo append_swap hashf_process_stin main utils
SRCS	:=	$(addprefix $(SRC_D), $(addsuffix .c, $(SRC)))
OBJ		:=	$(addprefix $(OBJ_D), $(SRCS:%.c=%.o))

END		:=	"\033[0;0m"
BLACK	:=	"\033[1;30m"
RED		:=	"\033[1;31m"
GREEN	:=	"\033[1;32m"
CYAN	:=	"\033[1;35m"
PURPLE	:=	"\033[1;36m"
WHITE	:=	"\033[1;37m"
YELLOW	:=	"\033[1;33m"


all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB) &> /dev/null
	@$(CC) -o $(NAME) $(CFLAGS) $(LFLAGS) $(OBJ)
	@echo $(GREEN) "\n- $@ is ready to be executed" $(END)

$(OBJ): | $(OBJ_D)

$(OBJ_D):
	@mkdir -p $(OBJ_D)$(SRC_D)

$(OBJ_D)%.o: %.c
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<
	@echo $(YELLOW)". \c" $(END)

clean: mclean
	@make clean -C $(LIB) &> /dev/null
	@echo $(RED) "\n- $(LIB).o files cleaned\n" $(END)
fclean: mfclean clean
	@make fclean -C $(LIB) &> /dev/null
	@echo $(RED) "\n- $(LIB).a is deleted\n" $(END)
re: fclean all

mclean:
	@rm -f $(OBJ)
	@echo $(RED) "\n- .o files cleaned\n" $(END)
mfclean: mclean
	@rm -f $(NAME)
	@rm -rf $(OBJ_D)
	@echo $(RED) "\n- $(NAME) is deleted\n" $(END)
mre: mfclean all
