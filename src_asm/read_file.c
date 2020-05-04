/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 17:13:21 by marvin            #+#    #+#             */
/*   Updated: 2020/05/04 18:37:24 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

// static int	is_correct(char *line)
// {
// 	int		i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (ft_strchr(LABEL_CHARS, line[i]) ||
// 		line[i] == SEPARATOR_CHAR || line[i] == DIRECT_CHAR ||
// 		line[i] == LABEL_CHAR || line[i] == COMMENT_CHAR)
// 			i++;
// 		else
// 			return (0);
// 	}
// 	return (1);
// }

static int	gnl_add_line(t_asm *asmb, int nb_line, char *line)
{
	t_gnl	*gnl;

	gnl = asmb->gnl;
	if (ft_strlen(line) == 0)
		return (1);
	// if (!is_correct(line))
	// 	return (0);
	if (gnl == NULL)
	{
		if (!(asmb->gnl = (t_gnl*)malloc(sizeof(t_gnl))))
			return (0);
		gnl = asmb->gnl;
	}
	else
	{
		while (gnl->next != NULL)
			gnl = gnl->next;
		if (!(gnl->next = (t_gnl*)malloc(sizeof(t_gnl))))
			return (0);
		gnl = gnl->next;
	}
	gnl->line = line;
	gnl->nb_line = nb_line;
	gnl->next = NULL;
	return (1);
}

void print_gnl(t_gnl *gnl)
{
	t_gnl *tmp;
	
	tmp = gnl;
	while (tmp)
	{
		printf("[%d]:%s\n", tmp->nb_line, tmp->line);
		tmp = tmp->next;
	}
}

int		read_file(t_asm *asmb, char *file_name)
{
	int		fd;
	char	*line;
	int		nb_line;

	nb_line = 1;
	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		return (0); //ошибка открытия файла
	}
	while (get_next_line(fd, &line) > 0)
	{
		if (!gnl_add_line(asmb, nb_line, line))
			return (0); //ошибка со строкой вывести строку и её номер
		nb_line++;
	}
	close(fd);
	print_gnl(asmb->gnl);
	return (1);
}
