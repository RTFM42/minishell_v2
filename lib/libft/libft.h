/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:47:29 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/25 20:11:42 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdint.h>

typedef struct s_errc
{
	void	(*exit)(const char *name, int num);
	int		(*print)(const char *name);
	int		(*setno)(const int no);
}	t_errc;

int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isspace(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
size_t			ft_strlcat(char *dest, char *src, unsigned int size);
size_t			ft_strlcpy(char *dest, const char *src, unsigned int size);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
char			*ft_strnstr(const char *s, const char *find, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);
void			*sf_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
int				ft_strictatoi(const char *str);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strnjoin(const char *s1, const char *s2, int n2);
char			*ft_strtrim(const char *s1, const char *set);
char			**ft_split(const char *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			*sf_calloc(size_t count, size_t size);
int				sf_close(int fd);
char			*sf_strdup(const char *s1);
int				sf_fopen(const char *path, int flag);
t_errc			err_constructor(void);

# define ERR err_constructor

#endif
