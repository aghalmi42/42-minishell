/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoderan <amoderan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 01:14:36 by aghalmi           #+#    #+#             */
/*   Updated: 2026/02/01 13:17:57 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_flags
{
	int	zero;
	int	dot;
	int	hashtag;
	int	space;
	int	plus;
	int	minus;
	int	width;
	int	precision;
}	t_flags;

typedef struct s_data
{
	char	*str;
	int		is_neg;
	int		is_zero;
	int		len;
	int		is_null;
	int		is_char_null;
}	t_data;

int					ft_isascii(int c);
int					ft_atoi(const char *s);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_lstsize(t_list *lst);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));

t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);

char				*ft_itoa(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);

int					ft_conversion_manag(char const *format, int *i, va_list list);
int					ft_printf(const char *format, ...);
int				check_flags(char c, t_flags *flag);
int		ft_free_conversion(t_flags *flag, t_data *data, char *res, int len);
void	priority_flags(t_flags *flag);
int		data_fail(t_flags *flag, char c);
void	parse_flag(t_flags *flag, char const *str, int *j, va_list list);
void	parse_width(t_flags *flag, char const *str, int *j, va_list list);
void	parse_precision(t_flags *flag, char const *str, int *j, va_list list);
void	ft_su(char *s, int size, unsigned int n);
void	ft_sh(char *s, int size, unsigned int n);
void	ft_sp(char *s, int size, unsigned long long n);
void	new_str_nb(int nb, t_data *data);
void	final_print(t_flags *flag, t_data *data, char *res, int *len);
t_flags	*new_flag(void);
t_data	*type_conversion(va_list list, char c);
t_data	*conversion_int(va_list list);
t_data	*conversion_string(va_list list);
t_data	*conversion_char(va_list list);
t_data	*conversion_hex(va_list list, int c);
t_data	*conversion_point(va_list list);
t_data	*conversion_percent(void);
t_data	*conversion_unsigned(va_list list);
t_data	*new_data(void);
char	*manag_precision(t_data *data, t_flags *flag, char c);
char	*manag_precision_nb(t_data *data, t_flags *flag);
char	*manag_precision_str(t_data *data, t_flags *flag);
char	*manag_prefix(char *str, t_data *data, t_flags *flag, char c);
char	*manag_prefix_int(char *str, t_flags *flag, t_data *data);
char	*manag_prefix_hex(char *str, char c);
char	*manag_width(char *str, t_flags *flag);
char	*manag_width_left(char *str, int nb_fill, char fill);
char	*manag_width_right(char *str, int nb_fill, char fill);
char	*conversion_final(t_data *data, t_flags *flag, char c);
char	*conversion_precision(t_data *data, t_flags *flag, char c);
char	*str_int(t_data *data, int nb);
char	*str_unsigned(t_data *data, unsigned int nb);
char	*str_hex(t_data *data, unsigned int nb);
char	*str_point(t_data *data, unsigned long long nb);
char	*ft_utoa(unsigned int n);
char	*ft_htoa(unsigned int n);
char	*ft_ptoa(unsigned long long n);

#endif