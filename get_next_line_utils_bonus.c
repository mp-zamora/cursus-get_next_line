/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpenas-z <mpenas-z@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:23:47 by mpenas-z          #+#    #+#             */
/*   Updated: 2024/06/19 13:14:26 by mpenas-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*get_new_line(t_list **current_fd)
{
	int		i;
	int		length;
	char	*buffer;

	i = 0;
	if ((*current_fd)->content == NULL)
		return (NULL);
	length = ft_strlen((*current_fd)->content);
	while ((*current_fd)->content[i] != '\n' && (*current_fd)->content[i])
		i++;
	if (i != length)
		return (truncate_content(&(*current_fd), i + 1));
	else if ((*current_fd)->content[i] == '\n')
	{
		buffer = (char *)malloc((length + 1) * sizeof(char));
		i = -1;
		while ((*current_fd)->content[++i])
			buffer[i] = (*current_fd)->content[i];
		buffer[i] = '\0';
		free ((*current_fd)->content);
		(*current_fd)->content = NULL;
		return (buffer);
	}
	return (NULL);
}

char	*add_content(char *s1, char *s2)
{
	char	*str;
	int		len1;
	int		len2;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	if (s1)
	{
		while (s1[++i])
			str[i] = s1[i];
		free (s1);
		i = -1;
	}
	while (s2[++i])
		str[i + len1] = s2[i];
	str[i + len1] = '\0';
	return (str);
}

char	*free_everything(t_list **node, int fd, char *str1)
{
	t_list	*list;
	t_list	*last;

	if (str1)
		free (str1);
	if ((*node)->fd == fd)
	{
		last = (*node)->next;
		free((*node)->content);
		free(*node);
		*node = last;
		return (NULL);
	}
	list = *node;
	while (list)
	{
		if (list->fd == fd)
			break ;
		last = list;
		list = list->next;
	}
	last->next = list->next;
	free(list->content);
	free(list);
	return (NULL);
}

char	*truncate_content(t_list **current_fd, int length)
{
	char	*string;
	char	*remainder;
	int		original_size;
	int		i;

	original_size = ft_strlen((*current_fd)->content);
	string = (char *)malloc((length + 1) * sizeof(char));
	remainder = (char *)malloc((original_size - length + 1) * sizeof(char));
	if (!string || !remainder)
		return (NULL);
	i = -1;
	while (++i < length && (*current_fd)->content[i])
		string[i] = (*current_fd)->content[i];
	string[i] = '\0';
	while ((*current_fd)->content[++i - 1])
		remainder[i - length - 1] = (*current_fd)->content[i - 1];
	remainder[i - length - 1] = '\0';
	free((*current_fd)->content);
	(*current_fd)->content = remainder;
	if (original_size == length)
	{
		free (remainder);
		(*current_fd)->content = NULL;
	}
	return (string);
}
