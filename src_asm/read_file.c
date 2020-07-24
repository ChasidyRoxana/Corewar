/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 17:13:21 by marvin            #+#    #+#             */
/*   Updated: 2020/07/24 18:47:43 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	gnl_add_line(t_asm *asmb, int nb_line, char *line)
{
	if (asmb->gnl == NULL)
	{
		if (!(asmb->gnl = (t_gnl*)malloc(sizeof(t_gnl))))
			return (error_common(ERR_MALLOC));
		asmb->gnl_last = asmb->gnl;
	}
	else
	{
		if (!(asmb->gnl_last->next = (t_gnl*)malloc(sizeof(t_gnl))))
			return (error_common(ERR_MALLOC));
		asmb->gnl_last = asmb->gnl_last->next;
	}
	asmb->gnl_last->line = line;
	asmb->gnl_last->nb_line = nb_line;
	asmb->gnl_last->next = NULL;
	return (1);
}

int			read_file(t_asm *asmb, char *file_name)
{
	int		fd;
	char	*line;
	int		nb_line;
	int		gnl;

	nb_line = 1;
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (error_common(ERR_OPEN_FILE));
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (!gnl_add_line(asmb, nb_line, line) || gnl == 1)
		{
			if (gnl == 1)
				error_common(ERR_NO_END);
			close(fd);
			return (0);
		}
		nb_line++;
	}
	close(fd);
	if (!asmb->gnl)
		return (error_common(ERR_FILE));
	return (1);
}
