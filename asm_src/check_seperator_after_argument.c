/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_seperator_after_argument.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 21:25:21 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/21 21:25:23 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_seperator_after_argument(char *file, int i)
{
	while (file[i] && file[i] != '\n')
	{
		if (file[i] == COMMENT_CHAR || file[i] == COMMENT)
			break ;
		if (file[i++] == SEPARATOR_CHAR)
			exit_lexical_error(file, i);
	}
}
