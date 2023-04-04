/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 23:55:24 by mfadil            #+#    #+#             */
/*   Updated: 2023/04/03 17:18:51 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_fd(int fd, char *str)
{
	char	*buf;
	int		read_bytes;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(str, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
	{
		if (str)
		{
			free(str);
			str = NULL;
		}
		return (NULL);
	}
	str = read_fd(fd, str);
	if (!str)
		return (NULL);
	line = get_lines(str);
	str = ft_new_left_str(str);
	return (line);
}
