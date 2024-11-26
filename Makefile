# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 11:54:42 by jaimesan          #+#    #+#              #
#    Updated: 2024/11/26 12:36:03 by jaimesan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#C FLAGS----------------------------------------------------------------------------------

CC = cc
CFLAGS = -W -W -W -I ./includes
AR = ar rcs
RM	= rm -rf
NOPRINT = --no-print-directory

#COLOURS---------------------------------------------------------------------------------

GREEN := \033[1;32m
RED := \033[1;31m
RESET := \033[0m

#FILES------------------------------------------------------------------------------------

SRCS = ./src/main.c ./src/init_struct.c ./src/get_full_name.c  ./src/get_commands.c \
	./src/builtins/print_env.c ./src/builtins/echo.c ./src/builtins/print_pwd.c  \
	./src/builtins/cd.c ./src/builtins/export.c ./src/builtins/print_history.c \
	./src/utils/mini_utils.c ./src/utils/error.c 

#OBJS--------------------------------------------------------------------------------------

OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

#Make---------------------------------------------------------------------------------------

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) $(LIBFT) 
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "[100%] $(GREEN)(Minishell) Compilation  | Minishell | successful!$(RESET)"

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)
	@echo "[100%] $(RED)(Minishell) Cleaning up exept compilers ..$(RESET)"

fclean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(OBJS) $(NAME)
	@echo "[100%] $(RED)(Minishell) Cleaning up...$(RESET)"

re: fclean all bonus

#RULES-------------------------------------------------------------------------------------

.PHONY:	all clean fclean re bonus

.SILENT:

#BONUS-------------------------------------------------------------------------------------

# bonus: $(OBJS_BONUS) $(LIBFT)
# 	$(CC) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)
# 	@echo "[100%] $(GREEN)(Pipex_Bonus) Compilation  | pipex_bonus | successful!$(RESET)"
#
# clean:
#	$(RM) $(OBJS_BONUS)
#
# fclean:
#	$(RM) $(OBJS_BONUS) $(NAME_BONUS)