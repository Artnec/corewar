/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 18:23:03 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 18:23:04 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstdel_end(t_list **alst)
{
	t_list	*temp;
	t_list	*temp2;
	int		i;

	if (!alst)
		return ;
	i = 0;
	temp = *alst;
	temp2 = *alst;
	while (temp->next)
	{
		temp = temp->next;
		i++;
	}
	free(temp);
	temp = NULL;
	while (i > 1)
	{
		temp2 = temp2->next;
		i--;
	}
	temp2->next = temp;
}
