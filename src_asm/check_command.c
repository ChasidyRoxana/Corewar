/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 13:25:40 by marvin            #+#    #+#             */
/*   Updated: 2020/07/02 20:54:44 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void		command_size(t_asm *asmb, t_command *command)
{
// 	Код операции — 1 байт
// 	Код типов аргументов (Нужен не для всех операций) — 1 байт
// 	Аргументы
	int		command_code;
	int		type_arg;
	int		args_size;
	t_args	*tmp;

	command_code = 1;
	type_arg = OP(command->op - 1).type_arg_code;
	args_size = 0;
	tmp = command->args;
	while (tmp)
	{
		if (tmp->type == T_REG)
			args_size += tmp->type;
		else if (tmp->type == T_IND)
			args_size += IND_SIZE;
		else if (tmp->type == T_DIR)
		{
			if (OP(command->op - 1).t_dir_size == 1)
				args_size += tmp->type;
			else
				args_size += 4;
		}
		tmp = tmp->next;
	}
	command->size += command_code + type_arg + args_size;
	asmb->header.prog_size += command->size;
}

int			check_op_name(char *com)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(com, OP(i).name))
			return (OP(i).op_code);
		i++;
	}
	return (-1);
}

static void	check_label_in_str(char *line, int *i, t_label *label)
{
	int		j;
	t_label	*l_tmp;

	j = 0;
	l_tmp = label;
	while (l_tmp->next)
		l_tmp = l_tmp->next;
	while (line[*i] && l_tmp->line[j] && line[*i] == l_tmp->line[j++])
		(*i)++;
	if (line[*i] == LABEL_CHAR && !l_tmp->line[j])
	{
		(*i)++;
		while (is_space(line[*i]))
			(*i)++;
	}
	else
		*i = skip_first_spaces(line);
}

int			find_command(t_asm *asmb, char *line)
{
	int		i;
	int		j;
	int		k;
	char	com[6];

	i = 0;
	j = 0;
	ft_memset((void*)com, 0, 6);
	while (is_space(line[i]))
		i++;
	if (asmb->comm_last->label)// если у команды есть метка, будем искать её в строке
		check_label_in_str(line, &i, asmb->comm_last->label);
	k = i;
	while (line[i] >= 'a' && line[i] <= 'z' && j < 6)
		com[j++] = line[i++];
	if (j > 5 || (j = check_op_name(com)) == -1)
		return (error_line(ERR_OP, asmb->comm_last->gnl_line, k));
	asmb->comm_last->op = j;
	if (!find_args(asmb, i + 1, asmb->comm_last->op - 1))
		return (0);
	command_size(asmb, asmb->comm_last);
	return (1);
}

int			check_command(t_asm *asmb)
{
	int		i;
	char	*line;

	line = asmb->gnl_last->line;
	i = skip_first_spaces(line);
	if (line[i] == '\0' || line[i] == COMMENT_CHAR)
		return (1);
	if (!new_command(asmb))
		return (0);
	if (!find_label(asmb))
		return (0);
	if (!asmb->gnl_last)
		return (error_common(ERR_NO_OP));
	asmb->comm_last->gnl_line = asmb->gnl_last;
	if (!find_command(asmb, asmb->gnl_last->line))
		return (0);
	return (1);
}
