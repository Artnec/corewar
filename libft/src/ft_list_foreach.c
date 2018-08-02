/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 15:50:26 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 15:50:28 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**Similar to ft_lstiter, but applies the function f to the content of each
**node rather than to the whole node.
*/

#include "../include/libft.h"

void	ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	if (!begin_list || !f)
		return ;
	while (begin_list)
	{
		f(begin_list->content);
		begin_list = begin_list->next;
	}
}
