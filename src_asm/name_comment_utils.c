/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 13:33:27 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/05/05 14:18:15 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

// проверка на переполнение
// return (1) - есть length_error, то есть места больше нет
// return (0) - все ок
int		length_error(int index, int length)
{
	// все-таки сколько записываем? (128 + 1) или (128) для имени, 
    // (2048) или (2048 + 1) для коммента (?)
    if (index >= length)
	{
		if (length == PROG_NAME_LENGTH)
			write(2, "The name of the champeon is too long\n", 38);
		else if (length == COMMENT_LENGTH)
			write(2, "The comment is too long\n", 25);
		return (1);
	}
	return(0);
}

// return (1) - все ок, (0) - ошибка (есть символы помимо таба и пробелов)
int		check_end_space(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
        // line[i] == 10 (?) - было в ft_strtrim, надо уточнить
		if (line[i] == 32 || line[i] == 10 || line[i] == '\t')
			i++;
		else
			return (0);
	}
	return (1);
}

int     error_name_comment(char *message, int nb_line)
{
    if (ft_strcmp(message, NAME_CMD_STRING) == 0)
    {
        write(2, "Error in name of the champeon in line: ", 40);
        ft_printf("%d\n", nb_line);
    }
    else if (ft_strcmp(message, COMMENT_CMD_STRING) == 0)
    {
        write(2, "Error in comment in line: ", 27);
        ft_printf("%d\n", nb_line);
    }
    return (0);
}

// скипаем пробелы и табы в начале, возвращаем индекс после них
int     skip_first_spaces(char *line)
{
    int i;

    i = 0;
    // line[i] == 10 (?) - было в ft_strtrim, надо уточнить
    while(line[i] == 32 || line[i] == 10 || line[i] == '\t')
		i++;
    return(i);
}