/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 13:33:27 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/05/06 20:43:58 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

// return (1) - все ок, (0) - ошибка (есть символы помимо таба и пробелов)
int		check_end_space(char *line)
{
	int i;

	i = 0;
	while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
		i++;
	if (!line[i] || line[i] == COMMENT_CHAR || line[i] == COMMENT_CHAR_2) // чекнуть в конце, нужно ли это везде, где вызывается эта функция
		return (1);
	else
		return (0);
}

// скипаем пробелы и табы в начале, возвращаем индекс после них
int     skip_first_spaces(char *line)
{
    int i;

    i = 0;
    while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
			i++;
    return(i);
}