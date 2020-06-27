/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 13:33:27 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/06/27 11:47:57 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		is_separator(char c)
{
	return (c == ' ' || c == '\0' || c == SEPARATOR_CHAR);
}

int		is_args(char c)
{
	return (c == '%' || c == 'r' || c == LABEL_CHAR
		|| (c >= '0' && c <= '9') || c == '-');
}

int		is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

// return (1) - все ок, (0) - ошибка (есть символы помимо таба и пробелов)
int		check_end_space(char *line)
{
	int i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (!line[i] || line[i] == COMMENT_CHAR || line[i] == COMMENT_CHAR_2) // чекнуть в конце, нужно ли это везде, где вызывается эта функция
		return (1);
	else
		return (0);
}

/*
** скипаем пробелы и табы в начале, возвращаем индекс после них
*/
int		skip_first_spaces(char *line)
{
	int i;

	i = 0;
	while (is_space(line[i]))
		i++;
	return (i);
}
