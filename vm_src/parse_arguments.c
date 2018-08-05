/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 14:50:07 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/25 14:50:09 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		str_compare(char *a, char *b)
{
	while (*a && *b && *a == *b)
	{
		a += 1;
		b += 1;
	}
	return (*a == '\0' && *b == '\0');
}

static int		get_bot_order(char *str)
{
	if (str == NULL)
		exit_error("not enough arguments after [-n] flag\n");
	if (*str == '1' && *(str + 1) == '\0')
		return (1);
	else if (*str == '2' && *(str + 1) == '\0')
		return (2);
	else if (*str == '3' && *(str + 1) == '\0')
		return (3);
	else if (*str == '4' && *(str + 1) == '\0')
		return (4);
	exit_error("only numbers 1 2 3 and 4 can be used after [-n] flag\n");
	return (0);
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

static char		*get_bot_name(char *str)
{
	int i;

	if (str == NULL)
		exit_error("missing bot name\n");
	i = 0;
	while (str[i])
		i++;
	if (*str == '-')
		exit_error("invalid flag\n");
	if (i <= 4)
		exit_error("bot name is invalid\n");
	if (str[i - 1] != 'r' || str[i - 2] != 'o' ||
		str[i - 3] != 'c' || str[i - 4] != '.')
		exit_error("bot name must have .cor extension\n");
	return (str);
}

int				get_cycle_to_start(char *str)
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

void			parse_arguments(int argc, char **argv, t_vm *vm, int i)
{
	int a[4];

	while (++i < 4)
		a[i] = 0;
	i = 0;
	if (str_compare(argv[1], "-v") && ++i)
	{
		vm->v = 1;
		i += ((vm->cycle_to_start = get_cycle_to_start(argv[2])) > 0 ? 1 : 0);
	}
	else if (str_compare(argv[1], "-dump"))
	{
		vm->dump = get_numer_of_cycles_before_dump(argv[2]);
		i += 2;
	}
	while (++i < argc)
	{
		if (vm->number_of_bots == MAX_PLAYERS)
			exit_error("too many players\n");
		if (str_compare(argv[i], "-n") &&
			(a[vm->number_of_bots] = get_bot_order(argv[i + 1])))
			i += 2;
		vm->bot_filenames[vm->number_of_bots++] = get_bot_name(argv[i]);
	}
	change_bot_order(a, vm);
}
