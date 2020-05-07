/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 15:02:42 by marvin            #+#    #+#             */
/*   Updated: 2020/05/06 23:22:55 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/* создаёт новый элемент списка команд, заполняет его нулями, ставит *prev,
** при ошибке возвращает 0
*/
int			new_command(t_asm *asmb)
{
	t_command	*tmp;

	tmp = NULL;
	if (!asmb->comm)
	{
		if (!(asmb->comm = (t_command*)malloc(sizeof(t_command))))
			return (error_line(ERR_MALLOC, NULL, 0));
		asmb->comm_last = asmb->comm;
	}
	else
	{
		if (!(asmb->comm_last->next = (t_command*)malloc(sizeof(t_command))))
			return (error_line(ERR_MALLOC, NULL, 0));
		tmp = asmb->comm_last;
		asmb->comm_last = asmb->comm_last->next;
	}
	ft_memset((void*)asmb->comm_last, 0, sizeof(t_command));
	asmb->comm_last->prev = tmp;
	return (1);
}

/* при ошибке возвращает 0
*/
int		parse_commands(t_asm *asmb)
{
	// t_gnl	*tmp_gnl;

	while (asmb->gnl_last)
	{
		// выделяем память на новую команду только когда находим команду или метку
		// if (!malloc_command(asmb))
		// 	return (-1);
		find_label(&asmb->gnl_last, asmb->comm_last);
		
		// check_command(); // find_first_word();
		// create_command();
		
		asmb->gnl_last = asmb->gnl_last->next;
		// asmb->op_last = asmb->op_last->next;
	}
	// printf("%d\n", asmb->gnl->nb_line);
	return (1);
}
