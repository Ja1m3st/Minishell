NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar crs

SRCS_STANDARD = standard/ft_atoi.c standard/ft_isalnum.c standard/ft_isalpha.c standard/ft_isascii.c \
	standard/ft_isdigit.c standard/ft_isprint.c standard/ft_memcpy.c standard/ft_memmove.c \
	standard/ft_memset.c standard/ft_strchr.c standard/ft_strlcat.c standard/ft_strlcpy.c \
	standard/ft_strlen.c standard/ft_strncmp.c standard/ft_strnstr.c standard/ft_strrchr.c \
	standard/ft_tolower.c standard/ft_toupper.c standard/ft_memchr.c standard/ft_memcmp.c \
	standard/ft_calloc.c standard/ft_bzero.c standard/ft_strdup.c standard/ft_substr.c \
	standard/ft_strjoin.c standard/ft_strtrim.c standard/ft_split.c standard/ft_itoa.c \
	standard/ft_strmapi.c standard/ft_striteri.c standard/ft_putchar_fd.c standard/ft_putstr_fd.c \
	standard/ft_putendl_fd.c standard/ft_putnbr_fd.c standard/ft_strcmp.c standard/ft_sqrt.c \
	standard/ft_strstr.c

SRCS_LNKD_LST = linked_lists/ft_lstnew.c linked_lists/ft_lstadd_front.c linked_lists/ft_lstsize.c \
	linked_lists/ft_lstlast.c linked_lists/ft_lstadd_back.c linked_lists/ft_lstdelone.c \
	linked_lists/ft_lstclear.c linked_lists/ft_lstiter.c linked_lists/ft_lstmap.c \
	linked_lists/ft_lstfree.c linked_lists/ft_lstinit_index.c linked_lists/ft_lstlast.c \
	linked_lists/ft_lstlen.c linked_lists/ft_lstmax_index.c standard/ft_strcmp.c standard/ft_split.c \
	linked_lists/ft_lst_isordered.c linked_lists/ft_check_valid_digits.c \
	linked_lists/ft_lstcheck_dupe.c standard/ft_isdigit.c standard/ft_atoi.c

SRCS_FTPRINTF = ft_printf/ft_printf.c ft_printf/ft_printf_utils.c \
	standard/ft_strchr.c standard/ft_strlen.c

SRC_GNL = get_next_line/get_next_line.c get_next_line/ft_read_line.c get_next_line/ft_save_line.c \
	get_next_line/ft_save_static.c get_next_line/get_next_line_utils.c

OBJS_STANDARD = $(SRCS_STANDARD:.c=.o)
OBJS_LNKD_LST = $(SRCS_LNKD_LST:.c=.o)
OBJS_FTPRINTF = $(SRCS_FTPRINTF:.c=.o)
OBJS_GNL = $(SRC_GNL:.c=.o)

all: $(NAME)

$(NAME): $(OBJS_STANDARD) $(OBJS_LNKD_LST) $(OBJS_FTPRINTF) $(OBJS_GNL)
	@$(AR) $(NAME) $(OBJS_STANDARD) $(OBJS_LNKD_LST) $(OBJS_FTPRINTF) $(OBJS_GNL)

standard: $(OBJS_STANDARD)
	@$(AR) $(NAME) $(OBJS_STANDARD)

linked_lists: $(OBJS_LNKD_LST)
	@$(AR) $(NAME) $(OBJS_LNKD_LST)

ft_printf: $(OBJS_FTPRINTF)
	@$(AR) $(NAME) $(OBJS_FTPRINTF)

gnl: $(OBJS_GNL)
	@$(AR) $(NAME) $(OBJS_GNL)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS_STANDARD) $(OBJS_LNKD_LST) $(OBJS_FTPRINTF) $(OBJS_GNL)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re standard linked_lists ft_printf gnl