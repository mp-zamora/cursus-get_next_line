/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:22:22 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/06/19 12:16:23 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_list
{
	int				fd;
	int				bytes_read;
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
int		read_from_fd(int fd, t_list **current_fd);
t_list	*find_current_fd(int fd, t_list *lst);
t_list	*create_new_fd(int fd);
t_list	*initialize_list(t_list **lst, int fd);
size_t	ft_strlen(const char *s);
char	*get_new_line(t_list **current_fd);
char	*add_content(char *s1, char *s2);
char	*free_everything(t_list **node, int fd, char *str1);
char	*truncate_content(t_list **current_fd, int length);

#endif
