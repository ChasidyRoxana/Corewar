/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_name_comment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 00:14:11 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/03 18:46:22 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

// return (0) - ошибка, (1) - все ок
int		check_next_line(char *line, int j, t_gnl **tmp, int length)
{
	int i;

	i = 0;
	if (j < length)
		line[j++] = '\n';
	while ((*tmp)->line[i] && (*tmp)->line[i] != '\"')
	{
		if (!length_error(j, length))
			return (0);
		line[j++] = (*tmp)->line[i++];
	}
	if ((*tmp)->line[i] == '\"')
	{
		if (!check_end_space(&(*tmp)->line[i + 1]))
			return (0);
	}
	else if (*tmp == NULL)
		return (0);
	else
	{
		*tmp = (*tmp)->next;
		if (!check_next_line(line, j, tmp, length))
			return (0);
	}
	return (1);
}

// return (0) - ошибка, (1) - все ок
int		create_name_comment(char *line, char *name_com, t_gnl **tmp, int length)
{
	int		i;
	int		j;

	j = 0;
	i = skip_first_spaces(line);
	if (line[i] && line[i++] == '\"')
	{
		while (line[i] && line[i] != '\"')
		{
			if (!length_error(j, length))
				return (0);
			name_com[j++] = line[i++];
		}
		if (!line[i])
		{
			*tmp = (*tmp)->next;
			if (!check_next_line(name_com, j, tmp, length))
				return (0);
		}
		else if (!check_end_space(&line[i + 1]))
			return (0);
	}
	else
		return (0);
	return (1);
}

int		proceed_name_comment(t_gnl **tmp, int i, t_asm *asmb)
{
	int error;

	error = 0;
	asmb->header.magic = COREWAR_EXEC_MAGIC;
	if (ft_strcmp((*tmp)->line + i, NAME_CMD_STRING) > 0)
	{
		error = create_name_comment((*tmp)->line + i + ft_strlen(NAME_CMD_STRING),
				asmb->header.prog_name, tmp, PROG_NAME_LENGTH);
		if (error == 0)
			return ((ft_strlen(asmb->header.prog_name) == PROG_NAME_LENGTH) ?
				0 : error_line(ERR_NAME, *tmp, -1));
		asmb->flag_name += 1;
		return (1);
	}
	else if (ft_strcmp((*tmp)->line + i, COMMENT_CMD_STRING) > 0)
	{
		error = create_name_comment((*tmp)->line + i + ft_strlen(COMMENT_CMD_STRING),
				asmb->header.comment, tmp, COMMENT_LENGTH);
		if (error == -1)
			return ((ft_strlen(asmb->header.comment) == COMMENT_LENGTH) ?
				0 : error_line(ERR_COMMENT, *tmp, -1));
		asmb->flag_comment += 1;
		return (1);
	}
	else
		return (error_common(ERR_NOT_COMMAND));
}

// return (0) - ошибка, (1) - все ок
int		find_name_comment(t_asm *asmb)
{
	t_gnl	*tmp;
	int		i;

	tmp = asmb->gnl;
	while (tmp)
	{
		if (asmb->flag_name == 1 && asmb->flag_comment == 1)
		{
			asmb->gnl_last = tmp;
			return (1);
		}
		i = skip_first_spaces(tmp->line);
		if (tmp->line[i] && tmp->line[i] == '.')
		{
			if (!proceed_name_comment(&tmp, i, asmb))
				return (0);
		}
		else if (tmp->line[i] && tmp->line[i] != COMMENT_CHAR
			&& tmp->line[i] != COMMENT_CHAR_2)
			return (error_line(ERR_SYNTAX, tmp, i));
		tmp = tmp->next;
	}
	if (asmb->flag_name != 1 || asmb->flag_comment != 1)
		return (error_common(ERR_NO_NAME_COMMENT));
	return (error_common(ERR_NO_OP));
}
