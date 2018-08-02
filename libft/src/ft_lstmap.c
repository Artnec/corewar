/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:32:49 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/12 16:32:50 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void		free_lst(t_list *lst)
{
	t_list	*prev;

	while (lst)
	{
		prev = lst;
		lst = lst->next;
		free(prev->content);
		free(prev);
	}
	lst = NULL;
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlst;
	t_list	*start;

	if (!lst || !f)
		return (NULL);
	newlst = ft_lstnew(f(lst)->content, f(lst)->content_size);
	if (!newlst)
		return (NULL);
	start = newlst;
	lst = lst->next;
	while (lst)
	{
		newlst->next = ft_lstnew(f(lst)->content, f(lst)->content_size);
		if (!newlst->next)
		{
			free_lst(start);
			return (NULL);
		}
		newlst = newlst->next;
		lst = lst->next;
	}
	return (start);
}
