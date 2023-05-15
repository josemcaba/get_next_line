#include <stdlib.h>
#include "get_next_line.h"

t_list *lst_new_node(void *content)
{
    t_list  *node;

    node = (t_list *)malloc(sizeof(t_list));
    if (!node)
        return(0);
    node->content = content;
    node->next = NULL;
    return (node);
}

void   lst_add_node(t_list **list, t_list *node)
{
    t_list  *last_node;

    if (!(*list))
        *list = node;
    else
    {
        last_node = *list;
        while (last_node->next)
            last_node = last_node->next;
        last_node->next = node;  
    }
}

// Libera todos los nodos salvo el ultimo
// Que se conserva para la siguiente lectura
// Por eso la lista es declarada static
void    lst_free(t_list **list)
{
    t_list  *next_node;

    while (*list && ((*list)->next))
    {
        next_node = (*list)->next;
        free((*list)->content);
        free(*list);
        *list = next_node;
    }
}

void mem_cpy_str(char *dst, char *src, size_t len)
{
    dst[len] = '\0';
    while (len--)
        dst[len] = src[len];
}

int str_len(char *str, int *nl_flag)
{
    int i;

    i = 0;
    while ((str[i] != '\n') && (str[i] != '\0'))
        i++;
    if (str[i] == '\n')
    {
        *nl_flag = 1;
        i++;
    }
    return (i);
}