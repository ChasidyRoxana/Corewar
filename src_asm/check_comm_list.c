/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_comm_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:49:43 by marvin            #+#    #+#             */
/*   Updated: 2020/06/26 16:12:08 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	set_args_type(t_command *comm)
{
	int		i;
	int		offset;
	t_args	*tmp;

	offset = 6;
	i = 0;
	tmp = comm->args;
	while (tmp)
	{
		if (tmp->type == T_IND)
			comm->args_type |= (3 << offset);
		else
			comm->args_type |= (tmp->type << offset);
		tmp = tmp->next;
		offset -= 2;
	}
	printf("ARGS_TYPE: %d\n", comm->args_type);
}

// static int	set_args(t_asm *asmb)
// {
// 	// пройтись по каждому аргументу, кроме T_REG; 
// 	// если метка, найти растояние до неё;
// 	// разобраться с урезанием по модулю;
// 	return (1);
// }

int			check_comm_list(t_asm *asmb)
{
	asmb->comm_last = asmb->comm;
	while (asmb->comm_last)
	{
		set_args_type(asmb->comm_last);
		// set_args(asmb);
		asmb->comm_last = asmb->comm_last->next;
	}
	return (1);
}
