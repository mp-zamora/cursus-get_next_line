/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:17:08 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/06/19 12:18:30 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*initialize_list(t_list **lst, int fd)
{
	t_list	*aux;

	if ((*lst) == NULL)
	{
		(*lst) = create_new_fd(fd);
		if (!(*lst))
			return (NULL);
	}
	if (find_current_fd(fd, (*lst)) == NULL)
	{
		aux = (*lst);
		while (aux->next)
			aux = aux->next;
		aux->next = create_new_fd(fd);
		return (aux->next);
	}
	return (find_current_fd(fd, (*lst)));
}

t_list	*create_new_fd(int fd)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->bytes_read = 0;
	new->content = NULL;
	new->next = NULL;
	return (new);
}

t_list	*find_current_fd(int fd, t_list *lst)
{
	if (!lst || fd < 0)
		return (NULL);
	while (lst->next != NULL)
	{
		if (lst->fd == fd)
			return (lst);
		lst = lst->next;
	}
	if (lst->fd == fd)
		return (lst);
	else
		return (NULL);
}

int	read_from_fd(int fd, t_list	**current_fd)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 0;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free (buffer);
		return (bytes_read);
	}
	buffer[bytes_read] = '\0';
	(*current_fd)->content = add_content((*current_fd)->content, buffer);
	free (buffer);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static t_list	*node;
	t_list			*current_fd;
	char			*line;

	if (fd < 0 || BUFFER_SIZE >= INT_MAX || BUFFER_SIZE < 1)
		return (NULL);
	current_fd = initialize_list(&node, fd);
	if (current_fd == NULL)
		return (NULL);
	current_fd->bytes_read = read_from_fd(fd, &current_fd);
	while (current_fd->bytes_read > 0)
	{
		line = get_new_line(&current_fd);
		if (line != NULL)
			return (line);
		current_fd->bytes_read = read_from_fd(fd, &current_fd);
	}
	if (current_fd->bytes_read < 0)
		return (free_everything(&node, fd, NULL));
	line = get_new_line(&current_fd);
	if (line)
		return (line);
	if (current_fd->content)
		return (truncate_content(&current_fd, ft_strlen(current_fd->content)));
	return (free_everything(&node, fd, line));
}
