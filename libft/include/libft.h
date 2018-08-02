/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myfts.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 17:14:57 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/04 17:15:00 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# define BUFF_SIZE 4096

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>
# include "wchar.h"
# include <locale.h>
# include <limits.h>
# include <inttypes.h>
# include <stdint.h>

# define SEP(x) x == ' ' || x == '\n' || x == '\t'
# define A(x) x == 'c' || x == 'C' || x == 's' || x == 'S' || x == 'p'
# define A1(x) x == 'd' || x == 'D' || x == 'i' || x == 'o' || x == 'O'
# define A2(x) x == 'u' || x == 'U' || x == 'x' || x == 'X' || x == '%'
# define B(x) x == '#' || x == '.' || x == '-' || x == '+' || x == 'l'
# define B1(x) x == 'h' || x == 'j' || x == 'z' || x == ' ' || x == 39
# define C(x) x == 'C' || x == 'S' || x == 'c' || x == 's' || x == '%'
# define D(x) (x >= 48 && x <= 57)

typedef	struct		s_p
{
	va_list				ap;
	int					i;
	int					j;
	char				*buf;
	char				*fmt;
	char				*spec;
	char				*without_spec;
	char				*tmp;
	size_t				buf_size;
	size_t				spec_size;
	size_t				ret;
	char				temp_c;
	char				*temp_s;
	wint_t				temp_wc;
	int					wd;
	int					awd;
	wchar_t				*temp_ws;
	int					temp_d;
	long				temp_ld;
	intmax_t			temp_im;
	uintmax_t			temp_um;
	size_t				temp_st;
	unsigned long		temp_ul;
	unsigned long long	temp_ull;
	unsigned int		temp_ui;
	size_t				fmt_len;
	int					sl_on;
	int					l_on;
	int					h_on;
	int					j_on;
	int					z_on;
	int					plus_on;
	int					minus_on;
	int					sharp_on;
	int					spaces;
	int					zero_on;
	int					width;
	int					precision;
	int					error;
	int					found;
	int					sharp_undef;
	int					minus_undef;
	int					cut;
	int					prec_found;
	int					minus_del;
	int					stop;
	int					dotnull;
	int					kostyl1;
	int					kostyl2;
	int					kostyl3;
	int					kostyl4;
	size_t				len;
}					t_p;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					ft_printf(const char *format, ...);
int					ft_abs(int nb);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_memalloc(size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
size_t				ft_strlen(const char *s);
void				look_for_specificators(t_p *p);
char				*ft_itoa_base(int value, int base);
size_t				check_the_buf(t_p *p, size_t len);
void				check_the_flags(t_p *p);
int					check_the_width(t_p *p);
char				*ft_ulxtoa_base(uintmax_t value, int base);
char				*ft_uixtoa_base(uintmax_t value, int base);
char				*ft_litoa_base(intmax_t value, int base);
void				funct_for_percent(t_p *p);
void				funct_for_p(t_p *p);
void				funct_for_d(t_p *p);
void				funct_for_s(t_p *p);
void				funct_for_c(t_p *p);
void				funct_for_wc(t_p *p);
void				funct_for_ws(t_p *p);
void				funct_for_u(t_p *p);
void				funct_for_o(t_p *p);
void				funct_for_x(t_p *p);
void				funct_for_big_x(t_p *p);
void				prefunct_for_big_d(t_p *p);
void				prefunct_for_d(t_p *p);
void				prefunct_for_big_u(t_p *p);
void				prefunct_for_u(t_p *p);
void				prefunct_for_wc(t_p *p);
void				prefunct_for_big_o(t_p *p);
void				prefunct_for_o(t_p *p);
void				prefunct_for_big_x(t_p *p);
void				prefunct_for_x(t_p *p);
void				minus_del(t_p *p);
void				more_spec(t_p *p);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
size_t				ft_strlcat(char *s1, const char *s2, size_t dstsize);
size_t				ft_strlen(const char *s);
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strnstr(const char *haystack, const char *needle,
	size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_memdel(void **ap);
void				*ft_memalloc(size_t size);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char const *s, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_factorial(int nb);
int					ft_sqrt(int nb);
int					ft_atoi_base(const char *str, int str_base);
void				ft_sort_int_tab(int *tab, unsigned int size);
char				*ft_strrev(char *str);
void				ft_print_bits(unsigned char octet);
int					ft_max(int *tab, unsigned int len);
unsigned char		ft_swap_bits(unsigned char octet);
int					ft_isprime(int count);
int					ft_add_prime_sum(int nb);
int					ft_list_size(t_list *begin_list);
int					ft_ispresent(char *s1, char *s2);
int					ft_pgcd(int a, int b);
void				ft_print_hex(unsigned int nbr);
char				**ft_split_whitespaces(char *str);
void				ft_list_foreach(t_list *begin_list, void (*f)(void *));
int					ft_power(int nb, int power);
int					ft_intlen(int nbr);
void				ft_lstadd_nth(t_list **alst, t_list *new, size_t n);
void				ft_lstadd_end(t_list **alst, t_list *new);
void				ft_lstdel_nth(t_list **list, size_t n);
void				ft_lstdel_end(t_list **alst);
void				ft_lstrev(t_list **list);
t_list				*ft_lstsplit(char const *s, char c);
int					ft_abs(int nb);
char				*ft_itoa_base(int value, int base);
int					get_next_line(const int fd, char **line);
void				ft_swap(int *a, int *b);

#endif
