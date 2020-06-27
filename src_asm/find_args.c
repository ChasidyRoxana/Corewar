/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:21:30 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/06/27 19:52:34 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			new_args(t_command *command)
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
	tmp->type = 0;
	tmp->arg = 0;
	tmp->arg_name = NULL;
	tmp->next = NULL;
	return (1);
}

int			write_arg(t_asm *asmb, t_args *tmp, int *i, int index_op)
{
	int last;

	if ((OP(index_op).args[asmb->comm_last->num_args] & tmp->type) == 0)
	{
		printf("Wrong arg type\n");
		return (0);
	}
	last = *i;
	if (asmb->gnl_last->line[*i] == '-')
	{
		(*i)++;
		if (!(asmb->gnl_last->line[*i] >= '0' && asmb->gnl_last->line[*i] <= '9'))
		{
			printf("POSLE '-' NET CIFR\n");
			return (0);
		}
	}
	// можно оставить только цикл, без if (?)
	// надо подумать над этим блоком
	if (asmb->gnl_last->line[*i] >= '0' && asmb->gnl_last->line[*i] <= '9')
		while (asmb->gnl_last->line[*i] >= '0' && asmb->gnl_last->line[*i] <= '9')
			(*i)++;
	else if (asmb->gnl_last->line[*i] == ':')
	{
		last = *i;
		++(*i);
		while (asmb->gnl_last->line[*i] && ft_strchr(LABEL_CHARS, asmb->gnl_last->line[*i]))
			(*i)++;
	}
	// + чекает вместо атои что на конце, например: "1s5" -> "ERROR ERROR ERROR"
	if (last == *i || !(is_separator(asmb->gnl_last->line[*i])))
	{
		printf("ERROR ERROR ERROR\n");
		return (0);
	}
	if (!(tmp->arg_name = ft_strnew(*i - last)))
		return (error_line(ERR_MALLOC, NULL, 0));
	ft_strncpy(tmp->arg_name, &asmb->gnl_last->line[last], (*i - last));
	asmb->comm_last->num_args++;
	return (1);
}

int			double_check_args(t_asm *asmb, int *i)
{
// проверяем, что идет после аргумента:
// 1. скипаем пробелы
// 2. если строка закончилась - все ок, выходим
// 3. если знак комментария - все ок, выходим
// 4. если запятая - надо проверить, что после нее есть аргумент, иначе - ошибка
	while (is_space(asmb->gnl_last->line[*i]))
		(*i)++;
	if (asmb->comm_last->num_args > 3)
	{
		printf("SLISHKOM MNOGO COMMAND\n");
		return (0);
	}
	else if (!asmb->gnl_last->line[*i])
		return (1);
	if (asmb->gnl_last->line[*i] == COMMENT_CHAR
		|| asmb->gnl_last->line[*i] == COMMENT_CHAR_2)
		return (1);
	else if (asmb->gnl_last->line[*i] == SEPARATOR_CHAR)
	{
		(*i)++;
		while (is_space(asmb->gnl_last->line[*i]))
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

int			proceed_args(t_asm *asmb, t_args *tmp, int *i, int index_op)
{
	if (asmb->gnl_last->line[*i] == 'r')
	{
		(*i)++;
		tmp->type = REG_CODE;
		if (!write_arg(asmb, tmp, i, index_op))
			return (0);
		// проверяем, что r >= 1 && r <= REG_NUMBER
		tmp->arg = ft_atoi(tmp->arg_name); // ft_atoi_check (?) - чекать, чтобы только цифры были
		if (!(tmp->arg >= 1 && tmp->arg <= REG_NUMBER))
		{
			printf("WRONG REG NUMBER\n");
			return (0);
		}
        // printf("REG: %d\n", tmp->arg);
	}
	else
	{
		if (asmb->gnl_last->line[*i] == '%')
		{
			tmp->type = DIR_CODE;
			(*i)++;
		}
		else if (asmb->gnl_last->line[*i] == ':' || (asmb->gnl_last->line[*i] >= '0'
			&& asmb->gnl_last->line[*i] <= '9') || asmb->gnl_last->line[*i] == '-')
			tmp->type = IND_CODE;
		// если метка - запоминаем строку с этой командой, чтобы потом вывести ошибку, если нужно
		if (asmb->gnl_last->line[*i] == ':')
			asmb->comm_last->label_line = asmb->gnl_last;
		if (!write_arg(asmb, tmp, i, index_op))
			return (0);
	}
	// if (tmp->type == T_DIR)
	// 	printf("DIR: %s\n", tmp->arg_name);
	// else if (tmp->type == T_IND)
	// 	printf("IND: %s\n", tmp->arg_name);
	return (1);
}

// обработать ошибки
// что записываем - 1/2/4? - размер T_DIR
// \n проверить в конце файла (после команд)
int			find_args(t_asm *asmb, int i, int index_op)
{
	t_args	*tmp;
	int		check;

	tmp = NULL;
	check = -1;
	while (is_space(asmb->gnl_last->line[i]))
		i++;
	while (asmb->gnl_last->line[i])
	{
		if (asmb->comm_last->num_args == OP(index_op).nb_arg)
		{
			printf("SLISHKOM MNOGO ARGS\n");
			return (0);
		}
		if (!new_args(asmb->comm_last))
			return (0);
		tmp = asmb->comm_last->args;
		while (tmp->next)
			tmp = tmp->next;
		if (is_args(asmb->gnl_last->line[i]))
		{
			if (!proceed_args(asmb, tmp, &i, index_op))
				return (0);
			if ((check = double_check_args(asmb, &i)) == 0)
				return (0);
			else if (check == 1)
			{
				if (asmb->comm_last->num_args != OP(index_op).nb_arg)
				{
					printf("SLISHKOM MALO ARGS\n");
					return (0);
				}
				return (1);
			}
		}
		else
			return (0);
	}
	return (1);
}
