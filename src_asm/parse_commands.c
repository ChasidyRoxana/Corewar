/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 15:02:42 by marvin            #+#    #+#             */
/*   Updated: 2020/07/03 19:52:32 by tkarpukova       ###   ########.fr       */
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
			return (error_common(ERR_MALLOC));
		asmb->comm_last = asmb->comm;
	}
	else
	{
		if (!(asmb->comm_last->next = (t_command*)malloc(sizeof(t_command))))
			return (error_common(ERR_MALLOC));
		tmp = asmb->comm_last;
		asmb->comm_last = asmb->comm_last->next;
	}
	ft_memset((void*)asmb->comm_last, 0, sizeof(t_command));
	asmb->comm_last->prev = tmp;
	asmb->comm_last->gnl_line = NULL;
	return (1);
}

int			parse_commands(t_asm *asmb)
{
	while (asmb->gnl_last)
	{
		if (!check_command(asmb))
			return (0);
		if (asmb->gnl_last)///////
			asmb->gnl_last = asmb->gnl_last->next;
	}
	if (!asmb->comm)
		return (error_common(ERR_NO_OP));
	if (!check_comm_list(asmb))
		return (0);
	return (1);
}
