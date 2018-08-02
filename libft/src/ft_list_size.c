/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 15:26:53 by rnaumenk          #+#    #+#             */
/*   Updated: 2017/11/18 15:26:54 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**Returns the number of all nodes in list.
*/

#include "../include/libft.h"

int		ft_list_size(t_list *begin_list)
{
	int i;

	i = 0;
	while (begin_list != NULL)
	{
		i++;
		begin_list = begin_list->next;
	}
	return (i);
}
