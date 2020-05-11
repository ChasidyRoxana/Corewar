/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 13:25:40 by marvin            #+#    #+#             */
/*   Updated: 2020/05/08 22:59:13 by tkarpukova       ###   ########.fr       */
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
	char	com[6];

	i = 0;
	j = 0;
	ft_memset((void*)com, 0, 6);
	while (is_space(line[i]))
		i++;
	if (asmb->comm_last->label)// если у команды есть метка, будем искать её в строке
		check_label_in_str(line, &i, asmb->comm_last->label);
	while (line[i] >= 'a' && line[i] <= 'z' && j < 6)
		com[j++] = line[i++];
	if (j == 6)
		return (0); // команда слишком длинная; com[j==5] должен быть концом строки
	printf("COM: .%s.\n", com);
	if ((j = check_op_name(com)) == -1)
		return (0); // обработать ошибку, что такой команды нет
	asmb->comm_last->op = j;
	if (!find_args(asmb, i + 1, asmb->comm_last->op - 1))
		return (0);
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
	return (1);
}
