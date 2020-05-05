/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 17:13:21 by marvin            #+#    #+#             */
/*   Updated: 2020/05/05 13:26:53 by tkarpukova       ###   ########.fr       */
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

// функция скипает пробелы и табы в начале строки и
// возвращает 1, если первый символ - точка, 0 - если не точка
int		check_dots(char *line)
{
	int i;

	i = 0;
	// line[i] == 10 (?)
	while (line[i] == 32 || line[i] == 10 || line[i] == '\t')
		i++;
	if (line[i] == '.')
		return (1);
	return (0);
}

int		read_file(t_asm *asmb, char *file_name)
{
	int		fd;
	char	*line;
	int		nb_line;
	int		dots; //

	nb_line = 1;
	dots = 0; //
	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		return (0); //ошибка открытия файла
	}
	while (get_next_line(fd, &line) > 0)
	{
		// проверка на количество '.' - должно быть ровно две точки (.name и .comment)
		// лучше сразу все чекнуть, а то потом придется снова по всем строкам проходиться
		if (check_dots(line)) //
			dots++; //
		if (!gnl_add_line(asmb, nb_line, line))
			return (0); //ошибка со строкой вывести строку и её номер
		nb_line++;
	}
	if (dots != 2) // 
		return (0); //
	close(fd);
	print_gnl(asmb->gnl);
	return (1);
}
