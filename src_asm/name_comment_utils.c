/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 13:33:27 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/05/06 16:24:02 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

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