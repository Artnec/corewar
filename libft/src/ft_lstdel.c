/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 15:43:31 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/12 15:43:32 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp;

	if (alst && *alst && del)
	{
		while (*alst)
		{
			temp = (*alst)->next;
			del((*alst)->content, sizeof((*alst)->content));
			free(*alst);
			(*alst) = temp;
		}
		*alst = NULL;
	}
}
