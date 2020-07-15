/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_label.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 22:09:02 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/15 23:40:38 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		malloc_label(t_command *command)
{
	t_label *tmp;

	tmp = command->label;
	if (command->label == NULL)
	{
		if (!(command->label = (t_label*)malloc(sizeof(t_label))))
			return (error_common(ERR_MALLOC));
		tmp = command->label;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_label*)malloc(sizeof(t_label))))
			return (error_common(ERR_MALLOC));
		tmp = tmp->next;
	}
	tmp->line = NULL;
	tmp->next = NULL;
	return (1);
}

int		create_label(t_asm *asmb, t_gnl *tmp, int *i)
{
	int		length;
	t_label	*tmp_label;

	length = *i - skip_first_spaces(tmp->line);
	tmp_label = asmb->comm_last->label;
	while (tmp_label->next)
		tmp_label = tmp_label->next;
	if (!(tmp_label->line = ft_strnew(length)))
		return (error_common(ERR_MALLOC));
	ft_strncpy(tmp_label->line, &tmp->line[skip_first_spaces(tmp->line)],
		length);
	if (check_end_space(&(tmp->line)[*i + 1]))
	{
		asmb->gnl_last = asmb->gnl_last->next;
		while (asmb->gnl_last)
		{
			*i = skip_first_spaces(asmb->gnl_last->line);
			if (asmb->gnl_last->line[*i] == COMMENT_CHAR ||
				asmb->gnl_last->line[*i] == COMMENT_CHAR_2)
				asmb->gnl_last = asmb->gnl_last->next;
			else
				return (-1);
		}
	}
	return (1);
}

int		find_label(t_asm *asmb)
{
	int		i;
	int		flag;
	t_gnl	*tmp;

	flag = -2;
	while (asmb->gnl_last)
	{
		tmp = asmb->gnl_last;
		i = skip_first_spaces(tmp->line);
		while (tmp->line[i] && ft_strchr(LABEL_CHARS, tmp->line[i]))
			i++;
		if (tmp->line[i] == LABEL_CHAR)
		{
			if (!malloc_label(asmb->comm_last))
				return (0);
			flag = create_label(asmb, tmp, &i);
			if (flag == 0 || flag == 1)
				return (flag);
		}
		else if (is_space(tmp->line[i]) || tmp->line[i] == '%')
			return (1);
		else
			return (error_line(ERR_LEXICAL, asmb->gnl_last, i));
	}
	return (1);
}
