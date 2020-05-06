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
	t_label *head;

	head = NULL;
    if (command->label == NULL)
	{
        if (!(command->label = (t_label*)malloc(sizeof(t_label))))
			return (error_line(ERR_MALLOC, NULL, 0));  
	}
	else
	{
		head = command->label;
        while (command->label->next)
			command->label = command->label->next;
		if (!(command->label->next = (t_label*)malloc(sizeof(t_label))))
			return (error_line(ERR_MALLOC, NULL, 0));
        command->label = command->label->next;
	}
    command->label->next = NULL;
    if (head)
        command->label = head;
	return (1);
}

int		find_label(t_gnl **gnl_last, t_command *op) 
{
	int		i;
	int		length;
	t_gnl	*tmp;
    
	tmp = *gnl_last;
	// ищем label'ы
    while (tmp)
	{
        // выделить память на список label'ов   
        // op->label = NULL;
        if (!malloc_label(op))//
            return (0);
        // op->label = (t_label*)malloc(sizeof(t_label));
		i = skip_first_spaces(tmp->line);
		while (tmp->line[i])
		{
            if (ft_strchr(LABEL_CHARS, tmp->line[i]))
				i++;
			else if (tmp->line[i] == LABEL_CHAR)
			{
                
                // записать label
				length = i - skip_first_spaces(tmp->line);
                op->label->line = ft_strnew(length);
				ft_strncpy(op->label->line, &tmp->line[skip_first_spaces(tmp->line)], length);
                // ft_strncpy(op->label->line, "violet", 6);
				printf("\nLABEL: .%s.\n", op->label->line);
                
                // прочекать строку - если она пустая, перейти дальше и прочекать есть ли label:
				// - есть: записываем, идем дальше
				// - нет: переставляем указатель гнл-ласт, ставим i на 0 и возвращаем его
				return (i);
			}
			else if (tmp->line[i] == COMMENT_CHAR || tmp->line[i] == COMMENT_CHAR)
				break ; // ? нужно перейти на след строку
			else 
				return (i); // ошибка - символ не из LABEL_CHAR или там команда и надо чекать
		}
		tmp = tmp->next;
	}
	return (i); //
}
