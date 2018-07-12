/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_bot_order.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 14:45:14 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/25 14:45:15 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		reorder(int *a, int j, char **tmp, t_vm *vm)
{
	int i;
	int n;

	i = -1;
	while (++i < vm->number_of_bots)
		tmp[i] = NULL;
	i = -1;
	while (++i < vm->number_of_bots)
	{
		if (a[i] != 0)
			tmp[a[i] - 1] = vm->bot_filenames[i];
	}
	i = 0;
	n = 0;
	while (j-- > 0)
	{
		while (tmp[n] != NULL)
			n++;
		while (a[i] != 0)
			i++;
		tmp[n] = vm->bot_filenames[i++];
	}
	i = -1;
	while (++i < vm->number_of_bots)
		vm->bot_filenames[i] = tmp[i];
}

void			change_bot_order(int *a, t_vm *vm)
{
	char	*tmp[4];
	int		i;
	int		j;

	if ((a[0] != 0 && (a[0] == a[1] || a[0] == a[2] || a[0] == a[3] ||
		a[0] == a[4])) || (a[1] != 0 && (a[1] == a[2] || a[1] == a[3] ||
		a[1] == a[4])) || (a[2] != 0 && (a[2] == a[3] || a[2] == a[4])) ||
		(a[3] != 0 && a[3] == a[4]))
		exit_error("two bots can't have same order\n");
	i = -1;
	j = 0;
	while (++i < vm->number_of_bots)
	{
		if (a[i] != 0 && a[i] != i + 1)
		{
			if (a[i] > vm->number_of_bots)
				exit_error("number after [-n] is bigger than number of bots\n");
			j++;
		}
	}
	if (j == 0)
		return ;
	j = 4 - j;
	reorder(a, j, tmp, vm);
}
