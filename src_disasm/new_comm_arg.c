/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_comm_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:59:22 by tpepperm          #+#    #+#             */
/*   Updated: 2020/07/15 22:06:47 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

int		new_command(t_disasm *disasm)
{
	if (!disasm->ops)
	{
		if (!(disasm->ops = (t_command*)malloc(sizeof(t_command))))
			return (0);
		disasm->ops_last = disasm->ops;
	}
	else
	{
		if (!(disasm->ops_last->next = (t_command*)malloc(sizeof(t_command))))
			return (0);
		disasm->ops_last = disasm->ops_last->next;
	}
	ft_memset((void*)disasm->ops_last, 0, sizeof(t_command));
	return (1);
}

int		new_arg(t_command *comm)
{
	t_arg	*tmp;

	if (!comm->args)
	{
		if (!(comm->args = (t_arg*)malloc(sizeof(t_arg))))
			return (0);
		comm->args->next = NULL;
	}
	else
	{
		tmp = comm->args;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_arg*)malloc(sizeof(t_arg))))
			return (0);
		tmp = tmp->next;
		tmp->next = NULL;
	}
	return (1);
}
