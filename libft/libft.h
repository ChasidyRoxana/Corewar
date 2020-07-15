/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:50:21 by croxana           #+#    #+#             */
/*   Updated: 2020/03/02 18:14:14 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

# define MIN_INT -2147483648
# define BUFF_SIZE 1
# define FD_SIZE 500

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_form
{
	va_list			*ptr;
	char			*format;
	int				fd;
	int				i;
	int				j;
	int				width;
	int				precision;
	int				plus;
	int				minus;
	int				space;
	int				zero;
	int				hash;
	int				l;
	int				ll;
	int				h;
	int				hh;
	int				llarge;
}					t_form;

int					ft_atoi(const char *str);
char				*ft_itoa(int n);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *restrict dst, const void *restrict src,
		int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *restrict dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
int					ft_power(int n, int pow);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char const *s, int fd);
char				*ft_strcat(char *restrict s1, const char *restrict s2);
char				*ft_strcdup(const char *s, int c);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dest, const char *src);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
int					ft_strequ(char const *s1, char const *s2);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *restrict dst, const char *restrict src,
		size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strncat(char *restrict s1, const char *restrict s2,
		size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *hay, const char *nee, size_t len);
char				*ft_strrchr(const char *s, int c);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
void				ft_swap(int *a, int *b);
int					get_next_line(const int fd, char **line);

int					ft_printf(const char *format, ...);

int					ft_flag_three(t_form *pt);
int					ft_flag_two(t_form *pt);
int					ft_flag_one(t_form *pt);
int					ft_print_sp(t_form *pt, int n, char c);
int					ft_count_b(unsigned long int n, int c);
void				ft_length_u(t_form *pt, unsigned long int *li);
void				ft_check_prec(t_form *pt, char **s, char side);
char				*ft_itoa_l(long l);
int					ft_printf_color(t_form *pt);

int					ft_printf_c(t_form *pt);
int					ft_printf_s(t_form *pt);
int					ft_printf_p(t_form *pt);
int					ft_printf_per(t_form *pt);
int					ft_printf_di(t_form *pt);
int					ft_printf_x(t_form *pt);
int					ft_printf_o(t_form *pt);
int					ft_printf_u(t_form *pt);
int					ft_printf_f(t_form *pt);
int					ft_printf_b(t_form *pt);
void				ft_free_split(char **tmp);

int					ft_fdprintf(int fd, const char *restrict format, ...);

int					ft_fdprintf_c(t_form *pt);
int					ft_fdprintf_per(t_form *pt);
int					ft_fdprintf_b(t_form *pt);
int					ft_fdprintf_di(t_form *pt);
int					ft_fdprintf_f(t_form *pt);
int					ft_fdprintf_p(t_form *pt);
int					ft_fdprintf_s(t_form *pt);
int					ft_fdprintf_u(t_form *pt);
int					ft_fdprintf_x(t_form *pt);
int					ft_fdprintf_o(t_form *pt);

#endif
