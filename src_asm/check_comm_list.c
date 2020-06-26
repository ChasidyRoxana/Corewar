/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_comm_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:49:43 by marvin            #+#    #+#             */
/*   Updated: 2020/05/12 16:49:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	set_args_type(t_command *comml)
{
	int		offset;
	t_args	*tmp;

	offset = 6;
	tmp = comml->args;
	while (tmp)
	{
		if (tmp->type == T_IND)
			comml->args_type |= (3 << offset);
		else
			comml->args_type |= (tmp->type << offset);
		offset -= 2;
		tmp = tmp->next;
	}
	// printf("ARGS_TYPE: %d\n", comml->args_type);
}

static int	check_label(t_command *comml)
{
	int		size;
	
	size = 0;
	return (size);
}

static int	set_args(t_command *comml)
{
	// пройтись по каждому аргументу, кроме T_REG; 
	// если метка, найти растояние до неё;
	// разобраться с урезанием по модулю;
	t_args	*tmpa;

	tmpa = comml->args;
	while (tmpa)
	{
		if (tmpa->type != T_REG)
		{
			if (tmpa->arg_name && tmpa->arg_name[0] == LABEL_CHAR)
				tmpa->arg = check_label(comml, );
			else
				tmpa->arg = ft_atoi(tmpa->arg_name);
		}
		tmpa = tmpa->next;
	}
	return (1);
}

int			check_comm_list(t_asm *asmb)
{
	asmb->comm_last = asmb->comm;
	while (asmb->comm_last)
	{
		set_args_type(asmb->comm_last);
		set_args(asmb->comm_last);
		asmb->comm_last = asmb->comm_last->next;
	}
	return (1);
}
