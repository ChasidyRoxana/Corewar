/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:21:30 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/05/08 15:43:39 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		new_args(t_command *command) 
{
	t_args *tmp;

	tmp = command->args;
    if (command->args == NULL)
	{
        if (!(command->args = (t_args*)malloc(sizeof(t_args))))
			return (error_line(ERR_MALLOC, NULL, 0));
		tmp = command->args;
	}
	else
	{
        while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_args*)malloc(sizeof(t_args))))
			return (error_line(ERR_MALLOC, NULL, 0));
        tmp = tmp->next;
	}
	tmp->arg = -1; //
    tmp->arg_name = NULL;
    tmp->next = NULL;
	return (1);
}

int			write_arg(t_asm *asmb, t_args *tmp, int *i)
{
	int last;
	
	// будем записывать число, если оно больше 16?
	last =  *i;
	if (asmb->gnl_last->line[*i] >= '0' && asmb->gnl_last->line[*i] <= '9')
		while (asmb->gnl_last->line[*i] >= '0' && asmb->gnl_last->line[*i] <= '9')
			(*i)++;
	else if (asmb->gnl_last->line[*i] == ':')
	{
		last = ++(*i);
		while (asmb->gnl_last->line[*i] && ft_strchr(LABEL_CHARS, asmb->gnl_last->line[*i]))
			(*i)++;
	}
	// ошибка, если после r не было цифр или если после цифр у нас
	// какие-то неправильные символы
	if (last == *i || !(is_separator(asmb->gnl_last->line[*i])))
	{
		printf("ERROR ERROR ERROR\n");
		return (0);
	}
	if (!(tmp->arg_name = ft_strnew(*i - last)))
		return (error_line(ERR_MALLOC, NULL, 0));
	ft_strncpy(tmp->arg_name, &asmb->gnl_last->line[last], (*i - last));
	asmb->comm_last->num_args++;
	return(1);
}

int			double_check_args(t_asm *asmb, int *i)
{
	// проверяем, что идет после аргумента:
	// 1. скипаем пробелы
	// 2. если строка закончилась - все ок, выходим
	// 3. если знак комментария - все ок, выходим
	// 4. если запятая - надо проверить, что после нее есть аргумент, иначе - ошибка
	while(is_space(asmb->gnl_last->line[*i]))
		(*i)++;
	if (asmb->comm_last->num_args > 3) 
	{
		printf("SLISHKOM MNOGO COMMAND\n");
		return(0);
	}
	else if (!asmb->gnl_last->line[*i])
		return (1);
	if (asmb->gnl_last->line[*i] == COMMENT_CHAR 
		|| asmb->gnl_last->line[*i] == COMMENT_CHAR_2)
		return (1); // сдвигать указатель gnl_last? (везде)
	else if (asmb->gnl_last->line[*i] == ',')
	{
		(*i)++;
		while(is_space(asmb->gnl_last->line[*i]))
			(*i)++;
		if (!asmb->gnl_last->line[*i])
		{
			printf("GDE ARGUMENT?\n");
			return (0);
		}
	}
	else 
	{
		printf("HRENOVIY SIMVOL\n");
		return (0);
	}
	return (-1);
}

int         proceed_args(t_asm *asmb, t_args *tmp, int *i)
{
    // чекаем регистр
    if (asmb->gnl_last->line[*i] == 'r') 
    {
        (*i)++;
        // записываю код из дефайна T_REG в op.h
        tmp->arg = 1;
        if(!write_arg(asmb, tmp, i))
            return (0);
        printf("REG: %s\n", tmp->arg_name);
    }
    // чекаем аргумент типа DIR
    else if (asmb->gnl_last->line[*i] == '%')
    {
        (*i)++;
        // tmp->arg = 10;
        // записываю код из дефайна T_DIR в op.h
        tmp->arg = 2;
        if(!write_arg(asmb, tmp, i))
            return (0);
        printf("DIR: %s\n", tmp->arg_name);
    } 
    // чекаем аргумент типа IND
    else if (asmb->gnl_last->line[*i] == ':' || (asmb->gnl_last->line[*i] >= '0' 
        && asmb->gnl_last->line[*i] <= '9'))
    {
        // tmp->arg = 11;
        // записываю код из дефайна T_DIR в op.h
        tmp->arg = 4;
        if(!write_arg(asmb, tmp, i))
            return (0);
        printf("IND: %s\n", tmp->arg_name);
    }
    return (1);
}

int			find_args(t_asm *asmb)
{
	int 	i;
	t_args	*tmp;
	int		check;
	
	i = 0;
	tmp = NULL;
	check = -1;
    // можно будет убрать, если функция будет получать индекс первого символа аргумента
	while(is_space(asmb->gnl_last->line[i]))
		i++;
	while (asmb->gnl_last->line[i])
	{
        // выделяем память на новый аргумент
		if (!new_args(asmb->comm_last))
			return(error_line(ERR_MALLOC, NULL, 0));
		tmp = asmb->comm_last->args;
		while (tmp->next)
			tmp = tmp->next;
		if (is_args(asmb->gnl_last->line[i]))
		{
            // чекаем аргумент и записываем его
            if (!proceed_args(asmb, tmp, &i))
                return (0);
			// чекаем символы после записанного аргумента
			check = double_check_args(asmb, &i);
			if (check == 0)
				return (0);
			else if (check == 1)
				return (1);
		}
		// если у нас какие-то левые символы, которых не может быть в команде
		else
			return (0);
	}
	return (1);
}