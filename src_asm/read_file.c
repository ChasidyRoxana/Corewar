/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 17:13:21 by marvin            #+#    #+#             */
/*   Updated: 2020/06/28 15:52:41 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/* фришит строку, зануляет указатель на неё и возвращает ret_nb
*/
int			free_str(char **str, int ret_nb)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (ret_nb);
}

/* пустая строка не добавляется в список, пробелы в начале строки скипаются;
** есть ошибка только с malloc(фришит line и выводит ошибку)
*/
static int	gnl_add_line(t_asm *asmb, int nb_line, char *line)
{
	if (ft_strlen(line) == 0)
		return (1);
	if (asmb->gnl == NULL)
	{
		if (!(asmb->gnl = (t_gnl*)malloc(sizeof(t_gnl))))
			return (error_line(ERR_MALLOC, NULL, 0, -1));
		asmb->gnl_last = asmb->gnl;
	}
	else
	{
		if (!(asmb->gnl_last->next = (t_gnl*)malloc(sizeof(t_gnl))))
			return (error_line(ERR_MALLOC, NULL, 0, -1));
		asmb->gnl_last = asmb->gnl_last->next;
	}
	asmb->gnl_last->line = line;
	asmb->gnl_last->nb_line = nb_line;
	asmb->gnl_last->next = NULL;
	return (1);
}
/////////////////////
void		print_gnl(t_gnl *gnl)
{
	t_gnl *tmp;

	tmp = gnl;
	while (tmp)
	{
		printf("[%d]:%s\n", tmp->nb_line, tmp->line);
		tmp = tmp->next;
	}
}//////////////////

int			read_file(t_asm *asmb, char *file_name)
{
	int		fd;
	char	*line;
	int		nb_line;
	int		gnl;

	nb_line = 1;
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (error_line(ERR_OPEN_FILE, NULL, 0, -1));
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		printf("gnl: %d\n", gnl);
		if (!gnl_add_line(asmb, nb_line, line))
			return (0);
		nb_line++;
		if (gnl == 1)
		{
			printf("Syntax error - unexpected end of input (Perhaps you forgot to end with a newline?)\n");
			return (0);
		}
	}
	close(fd);
	// if (asmb->last_line < asmb->gnl_last->nb_line)
	// {
	// 	printf("Syntax error - unexpected end of input (Perhaps you forgot to end with a newline?)\n");
	// 	return (0);
	// }
	// print_gnl(asmb->gnl);
	return (1);
}
