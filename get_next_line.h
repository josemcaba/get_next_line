/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaball <jocaball@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:50:52 by jocaball          #+#    #+#             */
/*   Updated: 2023/05/15 23:44:10 by jocaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 23
# endif

// # include "../libft/libft.h"
# include <sys/stat.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
	int				nl_flag;
	int				nl;
	int				len;
}	t_list;

char	*get_next_line(int fd);
t_list	*lst_new_node(char *content, int nl_flag, int len);
void	lst_add_node(t_list **list, t_list *node);
void	lst_free(t_list **lst);
void	mem_cpy_str(char *dst, char *src, size_t len);
int		str_len(char *str, int *nl_flag);

#endif
