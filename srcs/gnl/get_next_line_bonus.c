/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:04:32 by alex              #+#    #+#             */
/*   Updated: 2025/11/26 01:28:26 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*one_line(char **oversize)
{
	char	*res;
	char	*temp;
	int		i;

	if (!*oversize)
		return (NULL);
	i = ft_strlen_gnl(*oversize, '\n');
	res = ft_strjoin_gnl(NULL, *oversize, '\0', '\n');
	if (!res)
	{
		free(*oversize);
		*oversize = NULL;
		return (NULL);
	}
	if ((*oversize)[i] == '\n')
	{
		temp = one_line_eol(res, oversize);
		res = temp;
		i++;
	}
	temp = ft_strjoin_gnl(*oversize + i, NULL, '\0', '\0');
	free(*oversize);
	*oversize = temp;
	return (res);
}

char	*one_line_eol(char *res, char **oversize)
{
	char	*temp;

	temp = ft_strjoin_gnl(res, "\n", '\0', '\0');
	if (!temp)
	{
		free(res);
		free(*oversize);
		*oversize = NULL;
		return (NULL);
	}
	free(res);
	return (temp);
}

char	*new_oversize(char *oversize, int fd)
{
	int		nread;
	char	*buff;

	if (!oversize)
	{
		oversize = malloc(1);
		if (!oversize)
			return (NULL);
		oversize[0] = '\0';
	}
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
	{
		free(oversize);
		return (NULL);
	}
	nread = 1;
	oversize = read_lines(fd, oversize, buff, nread);
	if (oversize)
		free (buff);
	return (oversize);
}

char	*read_lines(int fd, char *oversize, char *buff, int nread)
{
	char	*str;

	while (nread > 0 && !(is_end_of_line_gnl(oversize)))
	{
		nread = read(fd, buff, BUFFER_SIZE);
		if (nread < 0)
		{
			free(buff);
			free(oversize);
			return (NULL);
		}
		if (nread == 0)
			break ;
		buff[nread] = '\0';
		str = ft_strjoin_gnl(oversize, buff, '\0', '\0');
		free(oversize);
		oversize = str;
		if (!str)
		{
			free(buff);
			return (NULL);
		}
	}
	return (oversize);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*oversize[1024];

	str = NULL;
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	oversize[fd] = new_oversize(oversize[fd], fd);
	if (!oversize[fd])
		return (NULL);
	else if (oversize[fd][0] == '\0')
	{
		free(oversize[fd]);
		oversize[fd] = NULL;
		return (NULL);
	}
	str = one_line(&oversize[fd]);
	if (oversize[fd] && oversize[fd][0] == '\0')
	{
		free(oversize[fd]);
		oversize[fd] = NULL;
	}
	return (str);
}
