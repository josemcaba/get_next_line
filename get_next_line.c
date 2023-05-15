#include "get_next_line.h"
#include <stdio.h>

// int read_line(char *buffer, t_list **list, int fd)
// {
//     int     buff_len;
//     int     len;
//     t_list  *node;
//     int     i;
//     int     nl_flag;

//     nl_flag = 0;
//     while (!nl_flag)
//     {
//         buff_len = read(fd, buffer, BUFFER_SIZE);
//         if (buff_len == -1)
//             return(-1);
//         buffer[buff_len] = '\0';
//         i = 0;
//         while (i < buff_len)
//         {
//             len = str_len(&(buffer[i]), &nl_flag);
//             node = lst_new_node((char *)malloc(len * sizeof(char) + 1));
//             if (!node)
//                 return(-1);
//             mem_cpy_str(node->content, &(buffer[i]), len);
//             lst_add_node(list, node);
//             i += len;
//         }
//     }
//     return (len);
// }

char *write_line(t_list **list)
{
    //char    *line;
    t_list  *next_node;
    int     nl_flag;

    if (!*list)
        return(NULL);
    nl_flag = 0;
    while (*list && !nl_flag)
    {
        printf((*list)->content);
        nl_flag = (*list)->nl_flag;
        next_node = (*list)->next;
        free((*list)->content);
        free(*list);
        *list = next_node;
    }
    return (NULL);
}

// char	*get_next_line(int fd)
// {
//     char    *buffer;
//     int     len;
//     char    *line;
//     static t_list  *list;

//     buffer = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
//     if (!buffer || !BUFFER_SIZE)
//         return (NULL);
//     len = read_line(buffer, &list, fd);
//     if (len < 0)
//         return (NULL);
//     free(buffer);
//     line = write_line(&list);
// //    lst_free(&list);
//     return (line);
// }

int	lst_add(char *buffer, t_list **list)
{
	int 	len;
	int		nl_flag;
	t_list	*node;

    len = str_len(buffer, &nl_flag);
    node = lst_new_node((char *)malloc(len * sizeof(char) + 1));
    if (!node)
    	return(-1);
    mem_cpy_str(node->content, buffer, len);
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
	while (!*list || !(*list)->nls)
	{
		buff_len = read(fd, buffer, BUFFER_SIZE);
        if (buff_len == -1)
            return(-1);
        buffer[buff_len] = '\0';
        i = 0;
        while (i < buff_len)
        {
			len = lst_add(&(buffer[i]), &(*list));
            // len = str_len(&(buffer[i]), &nl_flag);
            // node = lst_new_node((char *)malloc(len * sizeof(char) + 1));
            // if (!node)
            //     return(-1);
            // mem_cpy_str(node->content, &(buffer[i]), len);
            // lst_add_node(list, node);
            i += len;
        }
	}
	free(buffer);
	return (1);
}

char	*get_next_line(int fd)
{
    int     len;
    char    *line;
    static t_list  *list;

	if (!list || !list->nls)
		len = read_buff(&list, fd);
    if (len < 0)
        return (NULL);
    line = write_line(&list);
//    lst_free(&list);
    return (line);
}
