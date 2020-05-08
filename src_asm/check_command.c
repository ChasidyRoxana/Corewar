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

// int			find_command(t_asm *asmb)
// {
// 	return (1);
// }

int			check_args(t_asm *asmb)
{
	int		i;
	t_args	*tmp;

	i = 0;
	tmp = asmb->comm_last->args;
	// проверяем количество аргументов
	if (asmb->comm_last->num_args != (int)OP(3).nb_arg) // вместо OP(0) будет OP(номер_команды - 1(?))
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
	
	printf("OK: %d\n", OP(5).args[0]);
	printf("OK: %d\n", OP(5).args[1]);
	printf("OK: %d\n", OP(5).args[2]);
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
	// if (!find_command(asmb))
	// 	return (0);
	if (!find_args(asmb))
		return (0);
	if (!check_args(asmb))
		return (0);
	return (1);
}
