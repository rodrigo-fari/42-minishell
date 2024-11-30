/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-fari <rde-fari@student.42poto.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:07:10 by rde-fari          #+#    #+#             */
/*   Updated: 2024/08/12 20:56:56 by rde-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_from_file(char *s_buffer, int fd)
{
	char	*temp_buffer;
	int		bytes_read;

	temp_buffer = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_check_character(s_buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			if (s_buffer)
				free(s_buffer);
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[bytes_read] = '\0';
		s_buffer = ft_strjoin_gnl(s_buffer, temp_buffer);
	}
	free(temp_buffer);
	return (s_buffer);
}

char	*ft_extract_line(char *s_buffer)
{
	int		i;
	int		k;
	char	*line;

	if (s_buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (s_buffer[i] != '\n' && s_buffer[i])
		i++;
	k = i;
	if (s_buffer[i] == '\n')
		k++;
	line = ft_calloc_gnl(k + 1, sizeof(char));
	if (!line)
		return (NULL);
	ft_strcpy_nl(s_buffer, line, 1);
	return (line);
}

char	*ft_update_data(char *s_buffer)
{
	char	*new_data;
	int		start;

	start = 0;
	while (s_buffer[start] && s_buffer[start] != '\n')
		start++;
	if (s_buffer[start] == '\0')
	{
		free(s_buffer);
		return (NULL);
	}
	start++;
	new_data = ft_calloc_gnl(ft_strlen_gnl(s_buffer + start) + 1, sizeof(char));
	if (!new_data)
		return (NULL);
	ft_strcpy_nl(s_buffer + start, new_data, 0);
	free(s_buffer);
	return (new_data);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*s_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s_buffer = ft_read_from_file(s_buffer, fd);
	if (!s_buffer)
	{
		free(s_buffer);
		return (NULL);
	}
	line = ft_extract_line(s_buffer);
	s_buffer = ft_update_data(s_buffer);
	return (line);
}
