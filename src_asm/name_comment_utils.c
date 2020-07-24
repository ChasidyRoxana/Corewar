/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 13:33:27 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/24 18:41:24 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		is_separator(char c)
{
	return (is_space(c) || c == '\0' || c == SEPARATOR_CHAR);
}

int		is_args(char c)
{
	return (c == '%' || c == 'r' || c == LABEL_CHAR
		|| is_numeric(c) || c == '-');
}

int		is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int		check_end_space(char *line)
{
	int i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (!line[i] || line[i] == COMMENT_CHAR || line[i] == COMMENT_CHAR_2)
		return (1);
	else
		return (0);
}

int		skip_first_spaces(char *line)
{
	int i;

	i = 0;
	while (is_space(line[i]))
		i++;
	return (i);
}
