/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plang <plang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:32:02 by dbarrene          #+#    #+#             */
/*   Updated: 2024/04/18 18:19:29 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* ************************************************************************** */
/*  Headers                                                                   */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

/* ************************************************************************** */
/*  Macros                                                                    */
/* ************************************************************************** */
# define LMAX 9223372036854775807L
# define SMAX 18446744073709551615U
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 9
# endif
/* ************************************************************************** */
/*  Structs                                                                   */
/* ************************************************************************** */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
/*typedef struct s_split
{
	char		**split_arr;
	int			i;
	int			j;
	int			wc;
}					t_split;
*/
typedef struct s_qsplit
{
	char		**arr;
	int			i;
	int			j;
	char		temp;
}					t_qsplit;
typedef struct	s_wordc 
{
	int			i;
	int			flag;
	char		temp;
}					t_wordc;
/* ************************************************************************** */
/*  Original Libft                                                            */
/* ************************************************************************** */

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *str, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void*src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_substring(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
//char	**split_quotes(const char *str, char delim, char q, t_split *st);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f) (unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
char	**ft_quotesplit(const char *s, char c);
void	free_2d(char **arr);
void	ft_skip_chars(char **s, char c);
char	*ft_strjoin_flex(const char *s1, const char *s2, int flag);
/* ************************************************************************** */
/*  Ft_printf                                                                 */
/* ************************************************************************** */

int		ft_printf(const char *format, ...);
int		ft_putnbr_mod(int n, int *ptr);
int		ft_putchar_mod(int c, int *ptr);
int		ft_putstr_mod(char *s, int *ptr);
int		ft_put_unsigned(unsigned int n, int *ptr);
int		ft_format_check(char spec, va_list args, int *ptr);
int		ft_put_hex(unsigned long n, int caps, int *ptr);
int		ft_put_ptr(unsigned long n, int *ptr);
int		ft_iterate_format(const char *format, va_list args, int *ptr);

/* ************************************************************************** */
/*  Get_Next_line                                                             */
/* ************************************************************************** */
// size_t	ft_strlen_gnl(const char *str);
char	*ft_substr_mod(const char *s, unsigned int start, size_t len);
char	*ft_strjoin_mod(char *s1, const char *s2);
char	*get_next_line(int fd);
int		ft_strlen_mod(char *str, char c);
char	*ft_strchr_mod(const char *s, int c);
/* ************************************************************************** */
/*  Ft_Printerror                                                             */
/* ************************************************************************** */
int		ft_printerror(const char *format, ...);
int		ft_putnbr_mod_error(int n, int *ptr);
int		ft_putchar_mod_error(int c, int *ptr);
int		ft_putstr_mod_error(char *s, int *ptr);
int		ft_put_unsigned_error(unsigned int n, int *ptr);
int		ft_format_check_error(char spec, va_list args, int *ptr);
int		ft_put_hex_error(unsigned long n, int caps, int *ptr);
int		ft_put_ptr_error(unsigned long n, int *ptr);
int		ft_iterate_format_error(const char *format, va_list args, int *ptr);
#endif
