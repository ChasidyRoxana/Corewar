/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_name_comment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 00:14:11 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/24 18:47:28 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

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
	else
	{
		if (!(*tmp)->next)
			return (0);
		*tmp = (*tmp)->next;
		if (!check_next_line(line, j, tmp, length))
			return (0);
	}
	return (1);
}

int		create_namecom(char *line, char *name_com, t_gnl **tmp, int length)
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

int		check_name_comment(t_gnl **tmp, int i, t_asm *asmb, int length)
{
	int error;

	if (length == PROG_NAME_LENGTH)
	{
		error = create_namecom((*tmp)->line + i + ft_strlen(NAME_CMD_STRING),
					asmb->header.prog_name, tmp, PROG_NAME_LENGTH);
		if (error == 0)
			return ((ft_strlen(asmb->header.prog_name) == PROG_NAME_LENGTH) ?
				0 : error_line(ERR_NAME, *tmp, -1));
		else
			asmb->flag_name += 1;
	}
	else
	{
		error = create_namecom((*tmp)->line + i + ft_strlen(COMMENT_CMD_STRING),
				asmb->header.comment, tmp, COMMENT_LENGTH);
		if (error == 0)
			return ((ft_strlen(asmb->header.comment) == COMMENT_LENGTH) ?
				0 : error_line(ERR_COMMENT, *tmp, -1));
		else
			asmb->flag_comment += 1;
	}
	return (1);
}

int		proceed_name_comment(t_gnl **tmp, int i, t_asm *asmb)
{
	asmb->header.magic = COREWAR_EXEC_MAGIC;
	if (ft_strcmp((*tmp)->line + i, NAME_CMD_STRING) > 0)
		return (check_name_comment(tmp, i, asmb, PROG_NAME_LENGTH));
	else if (ft_strcmp((*tmp)->line + i, COMMENT_CMD_STRING) > 0)
		return (check_name_comment(tmp, i, asmb, COMMENT_LENGTH));
	else
		return (error_common(ERR_NOT_COMMAND));
}

int		find_name_comment(t_asm *asmb)
{
	int		i;
	t_gnl	*tmp;

	tmp = asmb->gnl;
	while (tmp)
	{
		i = skip_first_spaces(tmp->line);
		if (tmp->line[i] && tmp->line[i] == '.')
		{
			if (!proceed_name_comment(&tmp, i, asmb))
				return (0);
			if (asmb->flag_name == 1 && asmb->flag_comment == 1)
			{
				asmb->gnl_last = tmp;
				return (1);
			}
		}
		else if (tmp->line[i] && !is_comment(tmp->line[i]))
			return (is_found(asmb, tmp, i));
		tmp = tmp->next;
	}
	if (asmb->flag_name != 1 || asmb->flag_comment != 1)
		return (error_common(ERR_NO_NAME_COMMENT));
	return (error_common(ERR_NO_OP));
}
