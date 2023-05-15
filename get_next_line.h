#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 25
# endif

// # include "../libft/libft.h"
# include <sys/stat.h>
# include <stdlib.h>

typedef struct s_list
{
    char            *content;
    struct s_list   *next;
    int             nl_flag;
    int             nls;
}   t_list;

char	*get_next_line(int fd);
t_list *lst_new_node(char *content);
void     lst_add_node(t_list **list, t_list *node);
void    lst_free(t_list **lst);
void mem_cpy_str(char *dst, char *src, size_t len);
int str_len(char *str, int *nl_flag);

#endif
