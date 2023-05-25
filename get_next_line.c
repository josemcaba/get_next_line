/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaball <jocaball@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:51:14 by jocaball          #+#    #+#             */
/*   Updated: 2023/05/23 11:56:12 by jocaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str && (*str != (char)c))
		str++;
	if (*str == (char)c)
		return ((char *)str);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*read_file(int fd, char *buffer)
{
	char	*tmp_buff;
	ssize_t	len;
	char	*tmp;

	tmp_buff = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!tmp_buff)
		return (NULL);
	len = 1;
	while ((len > 0) && !ft_strchr(buffer, '\n'))
	{
		len = read(fd, tmp_buff, BUFFER_SIZE);
		if (len < 0)
		{
			if (buffer)
				free(buffer);
			free (tmp_buff);
			return (NULL);
		}
		tmp_buff[len] = '\0';
		tmp = ft_strjoin(buffer, tmp_buff);
		free(buffer);
		buffer = tmp;
	}
	free(tmp_buff);
	return (buffer);
}

char	*read_line(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = (char *)malloc(i * sizeof(char) + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = buffer[i];
	line[i + 1] = '\0';
	return (line);
}

char	*adjust_buff(char *buffer)
{
	size_t	i;
	char	*tmp_buff;
	size_t	j;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return(NULL);
	}
	tmp_buff = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i));
	if (!tmp_buff)
	{
		free(buffer);
		return(NULL);
	}
	i++;
	j = 0;
	while (buffer[i] != '\0')
		tmp_buff[j++] = buffer[i++];
	tmp_buff = '\0';
	free(buffer);
	return (tmp_buff);
}
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if ((fd < 0) || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = read_line(buffer);
	buffer = adjust_buff(buffer);
	return (line);
}
