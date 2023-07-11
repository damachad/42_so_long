/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:09:58 by damachad          #+#    #+#             */
/*   Updated: 2023/05/19 14:13:44 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_from(int fd, char *read_line)
{
	char	*buff;
	int		r_bytes;

	r_bytes = 1;
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (r_bytes > 0 && !ft_strchr(read_line, '\n'))
	{
		r_bytes = read(fd, buff, BUFFER_SIZE);
		if (r_bytes == -1)
		{
			free(buff);
			free(read_line);
			return (NULL);
		}
		buff[r_bytes] = '\0';
		read_line = ft_strjoin_2(read_line, buff);
	}
	free(buff);
	return (read_line);
}

char	*get_next_line(int fd)
{
	static char	*read_lines[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1023)
		return (NULL);
	read_lines[fd] = read_from(fd, read_lines[fd]);
	if (!read_lines[fd])
		return (NULL);
	line = ft_get_line(read_lines[fd]);
	read_lines[fd] = remain_text(read_lines[fd]);
	return (line);
}
