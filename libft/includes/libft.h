/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:41:22 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/13 12:24:24 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stddef.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	int				value;
	int				index;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int ch);
int		ft_tolower(int ch);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strstr(char *str, char *to_find);
long	ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strdelchar(const char *str, const char *chars);
void	*ft_realloc(void *ptr, size_t cur_size, size_t new_size);
void	ft_ptrdelchar(char *str, const char *chars);
char	*ft_strmerge(char *start_str, char *end_str);

//linked_lists
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_strcmp(const char *s1, const char *s2);
int		ft_check_valid_digits(char **temp, int j);
int		ft_lstcheck_dupe(t_list **stack_x);
int		ft_lst_isordered(t_list **stack_x);
size_t	ft_lstlen(t_list **stack_x);
t_list	*ft_lstnew(int value);
t_list	*ft_lstmax_index(t_list **stack_x);
t_list	*ft_lstlast(t_list **stack_x);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstinit_index(t_list **stack_x);
void	ft_lstfree(t_list **stack_x);

//get_next_line
char	*get_next_line(int fd);
char	*ft_read_line(int fd, char *total_chars);
char	*ft_save_line(char *total_chars);
char	*ft_save_static(char *total_chars);
void	*ft_calloc_z(size_t nmemb, size_t size);
char	*ft_strjoin_free(char *total_chars, char *temp);

//ftprintf
int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putnbr_dec(long nb);
int		ft_putnbr_hex(unsigned long long nb, int up_or_low);
int		ft_putptr(void *ptr);

#endif
