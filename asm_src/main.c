/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 17:50:15 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/22 17:50:19 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int argc, char **argv)
{
	int fd;
	// char	x[4] = "\x00\xea\x83\xf3";
	// char	a[4] = "\x10\x10\x10\x10";

	if (argc != 2)
	{
		printf("usage: ./asm filename\n");
		return (0);
	}
	fd = open(argv[1], O_WRONLY);
	// write(fd, x, 4);
	// write(fd, a, 4);
	close(fd);
	printf("asm\n");
	return (0);
}
