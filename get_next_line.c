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
#include "../libft/libft.h"

char	*alloc_line(t_list **list)
{
	int		nl_flag;
	t_list	*node;
	size_t	len;
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
	size_t	i;

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

ssize_t	add_node_to_list(char *buffer, t_list **list, ssize_t read_len)
{
	ssize_t	len;
	int		nl_flag;
	t_list	*node;
	char	*content;
	ssize_t	i;

	i = 0;
	len = 0;
	while ((i < read_len) && (len >= 0))
	{	
		len = str_len(&(buffer[i]), &nl_flag);
		content = (char *)malloc(len * sizeof(char) + 1);
		if (!content)
			return (-1);
		mem_cpy_str(content, &(buffer[i]), len);
		node = lst_new_node(content, nl_flag, len);
		if (!node)
		{
			free(content);
			return (-1);
		}
		lst_add_node(&(*list), node);
		i += len;
	}
	return (len);
}

ssize_t	read_buff_to_list(t_list **list, int fd)
{
	char	*buffer;
	ssize_t	read_len;
	ssize_t	node_len;

	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
		return (-1);
	read_len = 1;
	node_len = 0;
	while (read_len && (node_len >= 0) && (!*list || !(*list)->nl))
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len < 0)
		{
			lst_free(&(*list));
			break ;
		}
		buffer[read_len] = '\0';
		node_len = add_node_to_list(buffer, &(*list), read_len);
	}
	free(buffer);
	return (read_len * node_len);
}

void	read_file(int fd, char *buffer)
{
	char	*tmp_buff;
	ssize_t	len;
	char	*tmp;

	tmp_buff = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!tmp_buff)
		return;
	len = 1;
	while ((len > 0) && !ft_strchr(buffer, '\n'))
	{
		len = read(fd, tmp_buff, BUFFER_SIZE);
		if (len < 0)
		{
			if (buffer)
				free(buffer);
			free (tmp_buff);
			return;
		}
		tmp_buff[len] = '\0';
		tmp = ft_strjoin(buffer, tmp_buff);
		free(buffer);
		buffer = tmp;
	}
	free(tmp_buff);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if ((fd < 0) || BUFFER_SIZE <= 0)
		return (NULL);
	read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = buffer;
//	line = read_line(buffer);
//	adjust_buff(buffer);
	return (line);
}

// char	*get_next_line(int fd)
// {
// 	ssize_t			len;
// 	char			*line;
// 	static t_list	*list;

// 	if ((fd < 0) || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	len = 0;
// 	if (!list || !list->nl)
// 		len = read_buff_to_list(&list, fd);
// 	if ((len < 0) || !list)
// 	{
// 		lst_free(&list);
// 		return (NULL);
// 	}
// 	line = write_line(&list);
// 	if (!line)
// 	{
// 		lst_free(&list);
// 		return (NULL);
// 	}
// 	return (line);
// }
