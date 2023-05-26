/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocaball <jocaball@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:50:52 by jocaball          #+#    #+#             */
/*   Updated: 2023/05/26 14:08:15 by jocaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif

# define FD_MAX 2048

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
	int				nl_flag;
	size_t			nl;
	size_t			len;
}	t_list;

char	*get_next_line(int fd);
t_list	*lst_new_node(char *content, int nl_flag, size_t len);
void	lst_add_node(t_list **list, t_list *node);
void	lst_free(t_list **lst);
void	mem_cpy_str(char *dst, char *src, size_t len);
size_t	str_len(char *str, int *nl_flag);

#endif
