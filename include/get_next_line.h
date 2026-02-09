/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:06:37 by alex              #+#    #+#             */
/*   Updated: 2025/11/26 01:28:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2, char c_one, char c_two);
char	*one_line(char **oversize);
size_t	ft_strlen_gnl(const char *s, char c);
int		is_end_of_line_gnl(char *str);
char	*new_oversize(char *oversize, int fd);
char	*read_lines(int fd, char *oversize, char *buff, int nread);
char	*one_line_eol(char *res, char **oversize);

#endif