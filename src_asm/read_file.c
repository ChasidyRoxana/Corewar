/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 17:13:21 by marvin            #+#    #+#             */
/*   Updated: 2020/06/29 22:39:33 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/* фришит строку, зануляет указатель на неё и возвращает ret_nb
*/
// int			free_str(char **str, int ret_nb)
// {
// 	if (*str)
// 	{
// 		free(*str);
// 		*str = NULL;
// 	}
// 	return (ret_nb);
// }

/* пустая строка не добавляется в список, пробелы в начале строки скипаются;
** есть ошибка только с malloc(фришит line и выводит ошибку)
*/
static int	gnl_add_line(t_asm *asmb, int nb_line, char *line)
{
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (1);
	}
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
		// if (gnl == 1)
		// {
		// 	close(fd);
		// 	return (error_common(ERR_NO_END));
		// }
	}
	close(fd);
	if (!asmb->gnl)
		return (asmb, error_common(ERR_FILE));
	return (1);
}
