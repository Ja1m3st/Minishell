# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 11:54:42 by jaimesan          #+#    #+#              #
#    Updated: 2025/01/15 12:50:17 by jaimesan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#CFLAGS----------------------------------------------------------------------------------

CC 	= cc
CFLAGS 	= -Wall -Wextra -Werror -I ./includes
LDFLAGS = -fsanitize=address #DELETE AFTER
RM	= rm -rf
NOPRINT = --no-print-directory

#COLOURS---------------------------------------------------------------------------------

GREEN := \033[1;32m
RED := \033[1;31m
RESET := \033[0m

#FILES------------------------------------------------------------------------------------

SRCS = ./src/main/main.c ./src/main/init_struct.c ./src/parsing/exec_commands.c \
	./src/builtins/echo.c ./src/builtins/pwd.c ./src/builtins/cd.c \
	./src/builtins/export.c ./src/builtins/history.c ./src/builtins/unset.c \
	./src/builtins/variable_expansion.c ./src/utils/mini_utils.c ./src/utils/error.c  \
	./src/environment/print_env.c ./src/environment/dup_env.c \
	./src/environment/get_full_name.c ./src/parsing/pipe_commands.c ./src/main/handle_signals.c \
	./src/parsing/tokenize_commands.c ./src/utils/parsing_utils.c ./src/parsing/create_commands.c \
	./src/utils/command_utils.c ./src/parsing/process_commands.c ./src/parsing/quotations_commands.c \
	./src/utils/here_doc.c ./x_delete_after/delete_after.c ./src/builtins/resolve_path.c \
	./src/parsing/tokenize_commands_utils.c ./src/parsing/quotations_commands_utils.c \
	./src/utils/check_path.c
	

#OBJS--------------------------------------------------------------------------------------

OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

#Make---------------------------------------------------------------------------------------

all: $(NAME)

$(LIBFT):
	@$(MAKE) $(NOPRINT) -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<
#$(LDFLAGS)
$(NAME): $(OBJS) $(LIBFT) 
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) -lreadline 
	@echo "[100%] $(GREEN)(Minishell) Compilation  | Minishell | successful!$(RESET)"

clean:
	$(MAKE) $(NOPRINT) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)
	@echo "[100%] $(RED)(Minishell) Cleaning up exept compilers ..$(RESET)"

fclean:
	$(MAKE) $(NOPRINT) fclean -C $(LIBFT_DIR)
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
