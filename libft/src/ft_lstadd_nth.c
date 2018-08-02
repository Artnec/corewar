/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_nth.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 16:53:59 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 16:54:01 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_nth(t_list **alst, t_list *new, size_t n)
{
	t_list	*temp;
	size_t	i;

	if (!alst || !new)
		return ;
	if (n == 1)
	{
		new->next = *alst;
		*alst = new;
		return ;
	}
	i = 0;
	temp = *alst;
	if (n >= 2)
	{
		while (i < n - 2)
		{
			if (!temp)
				return ;
			temp = temp->next;
			i++;
		}
		new->next = temp->next;
		temp->next = new;
	}
}
