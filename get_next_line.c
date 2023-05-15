#include "get_next_line.h"
#include <stdio.h>

int read_line(char *buffer, t_list **list, int fd)
{
    int     buff_len;
    int     len;
    t_list  *node;
    int     i;

    while (1)
    {
        buff_len = read(fd, buffer, BUFFER_SIZE);
        if (buff_len == -1)
            return(-1);
        buffer[buff_len] = '\0';
        i = 0;
        while (i < buff_len)
        {
            len = str_len(&(buffer[i]));
            node = lst_new_node((char *)malloc(len * sizeof(char) + 1));
            if (!node)
                return(-1);
            mem_cpy_str(node->content, &(buffer[i]), len);
            lst_add_node(list, node);
            i += len;
        }
        if (node->content[len - 1] == '\n')
            break;
    }
    return (len);
}

char *write_line(t_list *list)
{
    //char    *line;

    if (!list)
        return(NULL);
    while (list)
    {
        printf(list->content);
        list = list->next;
    }
    return ("HOLA");
}

char	*get_next_line(int fd)
{
    char    *buffer;
    int     len;
    static t_list  *list;
    char    *line;

    buffer = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
    if (!buffer || !BUFFER_SIZE)
        return (NULL);
    len = read_line(buffer, &list, fd);
    if (len < 0)
        return (NULL);
    free(buffer);
    line = write_line(list);
    lst_free(&list);
    return (line);
}