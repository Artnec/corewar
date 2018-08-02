/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_nth.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 17:45:23 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 17:45:24 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstdel_nth(t_list **list, size_t n)
{
	t_list	*temp1;
	t_list	*temp2;
	size_t	i;

	if (!list || !*list)
		return ;
	i = 0;
	temp1 = *list;
	if (n == 1)
	{
		*list = temp1->next;
		free(temp1);
		temp1 = NULL;
		return ;
	}
	while (i++ < n - 2)
	{
		if (!temp1)
			return ;
		temp1 = temp1->next;
	}
	temp2 = temp1->next;
	temp1->next = temp2->next;
	free(temp2);
	temp2 = NULL;
}
