/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 18:00:01 by anesteru          #+#    #+#             */
/*   Updated: 2018/05/22 18:00:02 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>


# include <stdio.h>

typedef struct		s_asm
{
	char			*file;
	char			*name;
	char			*comment;
	char			*cor_file_name;
	int				cor_fd;
}					t_asm;

#endif
