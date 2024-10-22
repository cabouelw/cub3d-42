/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 15:54:56 by cabouelw          #+#    #+#             */
/*   Updated: 2020/12/21 12:46:56 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	lines(char **str, char **line, int fd)
{
	char	*temp;
	int		len;

	len = 0;
	while (str[fd][len] != '\n' && str[fd][len] != '\0')
		len++;
	if (str[fd][len] == '\n')
	{
		*line = ft_substr(str[fd], 0, len);
		temp = ft_strdup(str[fd] + len + 1);
		free(str[fd]);
		str[fd] = temp;
	}
	else
	{
		*line = ft_strdup(str[fd]);
		free(str[fd]);
		str[fd] = NULL;
		return (0);
	}
	return (1);
}

static int	result(int fd, char **line, char **str, int r)
{
	if ((!*str[fd] && !r))
	{
		*line = ft_strdup("");
		free(str[fd]);
		str[fd] = NULL;
		return (0);
	}
	return (lines(str, line, fd));
}

int			get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*str[4864];
	char		*temp;
	int			r;

	buffer = NULL;
	if (line == NULL || fd < 0 || fd > 4864 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!str[fd])
		str[fd] = ft_strdup("");
	while (!ft_strchr(str[fd], '\n') && (r = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[r] = '\0';
		temp = ft_strjoin(str[fd], buffer);
		free(str[fd]);
		str[fd] = temp;
	}
	free(buffer);
	return (r < 0 ? -1 : result(fd, line, str, r));
}
