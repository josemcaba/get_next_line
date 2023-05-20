/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaball <jocaball@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:51:14 by jocaball          #+#    #+#             */
/*   Updated: 2023/05/20 22:16:11 by jocaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*alloc_line(t_list **list)
{
	int		nl_flag;
	t_list	*node;
	int		len;
	char	*line;

	nl_flag = 0;
	node = *list;
	len = 0;
	while (node && !nl_flag)
	{
		len += node->len;
		nl_flag = node->nl_flag;
		node = node->next;
	}
	line = (char *)malloc(len * sizeof(char) + 1);
	return (line);
}

char	*write_line(t_list **list)
{
	t_list	*next_node;
	int		nl_flag;
	char	*line;
	int		i;

	line = alloc_line(&(*list));
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
	line[i] = '\0';
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
	// Provocar fallo de malloc y asegurar liberacion de buffer y list
	if (!content)
	{
//		lst_free(&(*list));
		return (-1);
	}
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
	int		read_len;
	int		len;

	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
		return (-1);
	read_len = 1;
	while (read_len && (!*list || !(*list)->nl) && (len >= 0))
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len < 0)
			break ;
		buffer[read_len] = '\0';
		i = 0;
		while ((i < read_len) && (len >= 0))
		{
			len = lst_add(&(buffer[i]), &(*list));
			if (len != -1)
				i += len;
		}
	}
	free(buffer);
	return (read_len); // No cambiar
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
	{
		lst_free(&list);
		return (NULL);
	}
	line = write_line(&list);
	return (line);
}
