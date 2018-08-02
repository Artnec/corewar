/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:51:02 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/12/20 12:51:03 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int		save(char **line, t_list *temp, char *buf, int i)
{
	char	*for_line;

	if (temp->content)
	{
		for_line = (char*)ft_memalloc(sizeof(char) *
			(ft_strlen(temp->content) + i + 1));
		ft_memcpy(for_line, temp->content, ft_strlen(temp->content));
		ft_memcpy(for_line + ft_strlen(temp->content), buf, i);
	}
	else
	{
		for_line = (char*)ft_memalloc(sizeof(char) * (i + 1));
		ft_memcpy(for_line, buf, i);
	}
	*line = for_line;
	if (temp->content)
		ft_memdel(&temp->content);
	if (buf[i + 1])
	{
		temp->content = (char*)ft_memalloc(sizeof(char) * (ft_strlen(buf) - i));
		ft_memcpy(temp->content, buf + (i + 1), ft_strlen(buf) - i - 1);
	}
	return (1);
}

static void		read_more(t_list **temp1, char *buf, int *j)
{
	int		i;
	char	*for_line;
	t_list	*temp;

	i = *j;
	temp = *temp1;
	if (!buf[i] && !(temp->content))
	{
		temp->content = (char*)ft_memalloc(sizeof(char) * (i + 1));
		ft_memcpy(temp->content, buf, i);
	}
	else if (!buf[i] && temp->content)
	{
		for_line = temp->content;
		temp->content = (char*)ft_memalloc(sizeof(char) *
			(ft_strlen(for_line) + i + 1));
		ft_memcpy(temp->content, for_line, ft_strlen(for_line));
		ft_memcpy(temp->content + ft_strlen(for_line), buf, i);
		ft_strdel(&for_line);
	}
}

static int		read_this_shit(const int fd, char **line, t_list *temp)
{
	char			buf[BUFF_SIZE + 1];
	int				res_of_read;
	int				i;

	ft_memset(buf, 0, BUFF_SIZE + 1);
	if (!(res_of_read = read(fd, buf, BUFF_SIZE)) && !temp->content)
		return (0);
	if (res_of_read == -1)
		return (-1);
	i = -1;
	while (res_of_read && ++i != (BUFF_SIZE + 1))
	{
		if (buf[i] == '\n')
			return (save(line, temp, buf, i));
		if (!buf[i])
		{
			read_more(&temp, buf, &i);
			ft_memset(buf, 0, BUFF_SIZE + 1);
			res_of_read = read(fd, buf, BUFF_SIZE);
			i = -1;
		}
	}
	*line = temp->content;
	temp->content = NULL;
	return (1);
}

static int		check_the_temp_content(const int fd, char **line, t_list *temp)
{
	char		*for_line;
	char		*temp1;
	size_t		i;

	i = 0;
	temp1 = temp->content;
	while (temp1 && temp1[i] && temp1[i] != '\n')
		i++;
	if (!temp1 || !temp1[i])
		return (read_this_shit(fd, line, temp));
	for_line = (char*)ft_memalloc(sizeof(char) * (i + 1));
	ft_memcpy(for_line, temp->content, i);
	*line = for_line;
	for_line = (char*)ft_memalloc(sizeof(char) *
		(ft_strlen(temp->content) - i));
	ft_memcpy(for_line, temp->content + (i + 1),
		ft_strlen(temp->content) - i - 1);
	ft_memdel(&temp->content);
	if (*for_line)
		temp->content = for_line;
	else
		free(for_line);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*list = NULL;
	t_list			*temp;

	if (fd <= -1 || fd > 4864 || !line)
		return (-1);
	*line = NULL;
	if (!list)
	{
		list = ft_lstnew(0, 0);
		list->content_size = fd;
	}
	temp = list;
	if (list && temp->content_size != (size_t)fd)
	{
		while (temp && temp->content_size != (size_t)fd)
			temp = temp->next;
		if (!temp)
		{
			temp = ft_lstnew(0, 0);
			temp->content_size = fd;
			temp->next = list;
			list = temp;
		}
	}
	return (check_the_temp_content(fd, line, temp));
}
