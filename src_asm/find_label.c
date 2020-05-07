/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_label.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 22:09:02 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/05/06 23:31:30 by tkarpukova       ###   ########.fr       */
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
			return (error_line(ERR_MALLOC, NULL, 0));
		tmp = command->label;
	}
	else
	{
        while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_label*)malloc(sizeof(t_label))))
			return (error_line(ERR_MALLOC, NULL, 0));
        tmp = tmp->next;
	}
    tmp->next = NULL;
	return (1);
}

int		find_label(t_asm *asmb)
{
	int		i;
	int		length;
	t_gnl	*tmp;
    
	while (asmb->gnl_last)// ищем label'ы
	{
		tmp = asmb->gnl_last;
		i = skip_first_spaces(tmp->line);
		while (ft_strchr(LABEL_CHARS, tmp->line[i]))
			i++;
		if (tmp->line[i] == LABEL_CHAR)
		{// записать label
			if (!malloc_label(asmb->comm_last))
				return (0);
			length = i - skip_first_spaces(tmp->line);
			if (!(asmb->comm_last->label->line = ft_strnew(length)))
				return (0);
			ft_strncpy(asmb->comm_last->label->line, &tmp->line[skip_first_spaces(tmp->line)], length);
			// ft_strncpy(op->label->line, "violet", 6);
			printf("\nLABEL: .%s.\n", asmb->comm_last->label->line);
			if (check_end_space(&(tmp->line)[i + 1]))
				asmb->gnl_last = asmb->gnl_last->next;
			else
				return (1);//если дальше команда
		}
		else if (is_space(tmp->line[i]))// или может быть '%'
			return (1);// если команда(' ')
		else
			return (0);// ошибка - символ не из LABEL_CHAR
	}
	return (1);
}
