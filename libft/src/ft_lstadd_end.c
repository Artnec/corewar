/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 17:33:22 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 17:33:29 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_end(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (!alst || !new)
		return ;
	temp = *alst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
