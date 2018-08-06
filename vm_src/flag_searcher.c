/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_searcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 20:58:00 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/08/06 20:58:01 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		get_cycle_to_start(char *str)
{
	int		i;
	long	num;

	if (str == NULL)
		exit_error("corewar needs at least one bot to work\n");
	num = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		num = (num * 10) + str[i++] - 48;
	if (i == 0 || str[i] != '\0')
		return (0);
	else if (num >= 1000000000)
		exit_error("to many cycles\n");
	else if (i > 10)
		exit_error("incorect number of cycles\n");
	return (num);
}

static int		get_numer_of_cycles_before_dump(char *str)
{
	int		i;
	long	num;

	if (str == NULL)
		exit_error("corewar needs at least one bot to work\n");
	num = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		num = (num * 10) + str[i++] - 48;
	if (i == 0 || str[i] != '\0')
		exit_error("incorect number of cycles\n");
	else if (num >= 1000000000)
		exit_error("to many cycles\n");
	else if (i > 10)
		exit_error("incorect number of cycles\n");
	return (num);
}

void			flag_searcher(t_vm *vm, char **argv, int *i)
{
	if (str_compare(argv[1], "-a") && ++(*i))
		vm->a_flag = 1;
	else if (str_compare(argv[1], "-v") && ++(*i))
	{
		vm->v = 1;
		*i += ((vm->cycle_to_start = get_cycle_to_start(argv[2])) > 0 ? 1 : 0);
	}
	else if (str_compare(argv[1], "-dump"))
	{
		vm->dump = get_numer_of_cycles_before_dump(argv[2]);
		*i += 2;
	}
}
