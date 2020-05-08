/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 13:25:40 by marvin            #+#    #+#             */
/*   Updated: 2020/05/08 15:55:55 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

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

int			find_command(t_asm *asmb, char *line)
{
	t_label	*l_tmp;
	int		i;
	int		j;
	// char	*line;
	char	com[6];

	ft_memset((void*)com, 0, 6);
	// line = asmb->gnl_last->line;
	// printf("Line: .%s.\n", line);
	i = 0;
	j = 0;
	while (is_space(line[i]))
		i++;
	if (asmb->comm_last->label)// если у команды есть метка, будем искать её в строке
	{
		l_tmp = asmb->comm_last->label;
		while (l_tmp->next)
			l_tmp = l_tmp->next;
		while (line[i] && l_tmp->line[j] && line[i] == l_tmp->line[j++])
			i++;
		if (line[i] == LABEL_CHAR && !l_tmp->line[j])
		{
			while (is_space(line[++i]))
				;
		}
		else
			i = skip_first_spaces(line);
	}
	j = 0;
	while (line[i] >= 'a' && line[i] <= 'z')
		com[j++] = line[i++];
	printf("COM: .%s.\n", com);
	if ((j = check_op_name(com)) == -1)
		return (0);
	// printf("OP_CODE: %d\n", j);
	asmb->comm_last->op = j;
	if (!find_args(asmb, i + 1))
		return (0);
	return (1);
}

int			check_args(t_asm *asmb)
{
	int		i;
	t_args	*tmp;

	i = 0;
	tmp = asmb->comm_last->args;
	// проверяем количество аргументов
	if (asmb->comm_last->num_args != (int)OP(asmb->comm_last->op - 1).nb_arg)
	{
		printf("WRONG NUMBER OF ARGUMENTS\n");
		return (0);
	}
	// проверяем тип аргументов
	// while (tmp)
	// {
	// 	while(OP(0).args[i])
	// 	{
	// 		if (tmp->arg == OP(0).args[i])
	// 			i++;
	// 		else
	// 			return (0);
	// 	}
	// 	tmp = tmp->next;
	// }
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
	if (!find_command(asmb, asmb->gnl_last->line))
		return (0);
	if (!check_args(asmb))
		return (0);
	return (1);
}
