/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpatiaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 14:51:26 by kpatiaka          #+#    #+#             */
/*   Updated: 2018/08/07 14:51:28 by kpatiaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	sound_stuff(t_vm *vm, int i)
{
	if (vm->v == 1 || vm->v == -1)
	{
		if (i == 0)
			system("afplay corsound/t3.mp3&");
		else if (i == 1)
			system("afplay corsound/dramatic.swf.mp3&");
		else if (vm->cycle >= vm->cycle_to_start && vm->v != -1)
		{
			if (i == 2)
				system("afplay corsound/ws.mp3&");
			else if (i == 3)
				system("afplay corsound/oh_my.mp3&");
		}
	}
}
