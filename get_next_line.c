/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaball <jocaball@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:51:14 by jocaball          #+#    #+#             */
/*   Updated: 2023/05/16 22:34:29 by jocaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

void	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
}

char	*write_line(t_list **list)
{
	t_list	*next_node;
	int		nl_flag;
	char	*line;
	int		len;
	int		i;

	if (!*list)
		return (NULL);
	nl_flag = 0;
	next_node = *list;
	len = 0;
	while (next_node && !nl_flag)
	{
		len += next_node->len;
		nl_flag = next_node->nl_flag;
		next_node = next_node->next;
	}
	line = (char *)malloc(len * sizeof(char));
	if (!line)
		return (NULL);
	nl_flag = 0;
	i = 0;
	while (*list && !nl_flag)
	{
		nl_flag = (*list)->nl_flag;
		mem_cpy_str(&line[i], (*list)->content, (*list)->len);
		i += (*list)->len;
		next_node = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = next_node;
	}
	return (line);
}

int	lst_add(char *buffer, t_list **list)
{
	int		len;
	int		nl_flag;
	t_list	*node;
	char	*content;

	len = str_len(buffer, &nl_flag);
	content = (char *)malloc(len * sizeof(char) + 1);
	if (!content)
		return (-1);
	mem_cpy_str(content, buffer, len);
	node = lst_new_node(content, nl_flag, len);
	if (!node)
		return (-1);
	lst_add_node(&(*list), node);
	return (len);
}

int	read_buff(t_list **list, int fd)
{
	char	*buffer;
	int		i;
	int		buff_len;
	int		len;

	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer || !BUFFER_SIZE)
		return (-1);
	buff_len = 1;
	while (buff_len && (!*list || !(*list)->nl))
	{
		buff_len = read(fd, buffer, BUFFER_SIZE);
		if (buff_len < 0)
			break ;
		buffer[buff_len] = '\0';
		i = 0;
		while (i < buff_len)
		{
			len = lst_add(&(buffer[i]), &(*list));
			i += len;
		}
	}
	free(buffer);
	return (buff_len);
}

char	*get_next_line(int fd)
{
	int				len;
	char			*line;
	static t_list	*list;

	if ((fd < 0) || BUFFER_SIZE <= 0)
		return (NULL);
	len = 0;
	if (!list || !list->nl)
		len = read_buff(&list, fd);
	if ((len < 0) || !list)
		return (NULL);
	line = write_line(&list);
	return (line);
}
