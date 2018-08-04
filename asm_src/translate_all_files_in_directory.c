/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_all_files_in_directory.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:33:51 by anesteru          #+#    #+#             */
/*   Updated: 2018/07/22 20:33:53 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			initiate_structure(t_asm *s)
{
	s->name = NULL;
	s->comment = NULL;
	s->size = 0;
	s->op_labels = NULL;
}

void			free_all(t_asm *s)
{
	t_list *tmp;

	while (s->op_labels)
	{
		tmp = s->op_labels;
		s->op_labels = s->op_labels->next;
		free(tmp->str);
		free(tmp);
	}
	free(s->file);
	free(s->comment);
	free(s->name);
	free(s->cor_file_name);
}

static void		get_file_dir_slash_filename(char *dir, char *file, char *name)
{
	int i;
	int n;

	i = -1;
	while (dir[++i])
		name[i] = dir[i];
	name[i++] = '/';
	n = 0;
	while (file[n])
		name[i++] = file[n++];
	name[i] = '\0';
}

void			translate_all_files_in_directory(char *dir_name, t_asm *s)
{
	struct dirent	*entry;
	char			name[512];
	DIR				*dir;
	int				len;

	dir = opendir(dir_name);
	if (dir == NULL)
		exit_error("Error: bad directory name\n");
	while ((entry = readdir(dir)))
	{
		len = str_len(entry->d_name);
		if (entry->d_name[0] == '.' || len < 3 || entry->d_name[len - 1] != 's'
			|| entry->d_name[len - 2] != '.')
			continue ;
		initiate_structure(s);
		get_file_dir_slash_filename(dir_name, entry->d_name, name);
		read_s_file(name, s);
		if (validate_and_translate_into_machine_code(s))
			exit_error("Error: empty source file\n");
		create_cor_file(name, s);
		write_into_cor_file(s);
		free_all(s);
	}
	closedir(dir);
}
