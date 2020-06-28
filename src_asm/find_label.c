/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_label.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 22:09:02 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/06/27 12:00:53 by tkarpukova       ###   ########.fr       */
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
			return (error_line(ERR_MALLOC, NULL, 0, -1));
		tmp = command->label;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_label*)malloc(sizeof(t_label))))
			return (error_line(ERR_MALLOC, NULL, 0, -1));
		tmp = tmp->next;
	}
	tmp->line = NULL;
	tmp->next = NULL;
	return (1);
}

int		find_label(t_asm *asmb)
{
	int		i;
	int		length;
	t_gnl	*tmp;
	t_label *tmp_label;

	while (asmb->gnl_last)
	{
		tmp = asmb->gnl_last;
		i = skip_first_spaces(tmp->line);
		// если после строки с меткой будут пустые строки надо их скипать
		// if (tmp->line[i] == '\0')
		// 	asmb->gnl_last = asmb->gnl_last->next;
		// добавила пока tmp->line[i], иначе какая-то хня
		while (tmp->line[i] && ft_strchr(LABEL_CHARS, tmp->line[i]))
			i++;
		if (tmp->line[i] == LABEL_CHAR)
		{
			if (!malloc_label(asmb->comm_last))
				return (error_line(ERR_MALLOC, NULL, 0, -1));
			length = i - skip_first_spaces(tmp->line);
			// добавила проход до конца label'ов, чтобы записать новую метку
			tmp_label = asmb->comm_last->label;
			while (tmp_label->next)
				tmp_label = tmp_label->next;
			if (!(tmp_label->line = ft_strnew(length)))
				return (error_line(ERR_MALLOC, NULL, 0, -1)); // добавила ERR_MALLOC для вывода ошибки
			ft_strncpy(tmp_label->line, &tmp->line[skip_first_spaces(tmp->line)], length);
			// printf("\nLABEL: .%s.\n", tmp_label->line);
			if (check_end_space(&(tmp->line)[i + 1]))
				asmb->gnl_last = asmb->gnl_last->next;
			else
				return (1);//если дальше команда
		}
		else if (is_space(tmp->line[i]) || tmp->line[i] == '%'
			|| tmp->line[i] == ',' || tmp->line[i] == '\0')// или может быть '%' или ',' (sti9,%8 например) или '\0'
			return (1);// если команда(' ')
		else
			return (0);// ошибка - символ не из LABEL_CHAR
	}
	return (1);
}
