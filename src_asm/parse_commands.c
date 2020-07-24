/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 15:02:42 by marvin            #+#    #+#             */
/*   Updated: 2020/07/24 00:44:07 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

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
		if (asmb->gnl_last)
			asmb->gnl_last = asmb->gnl_last->next;
	}
	if (!asmb->comm)
		return (error_common(ERR_NO_OP));
	if (!check_comm_list(asmb))
		return (0);
	return (1);
}

int			delete_empty_lines(t_asm *asmb)
{
	t_gnl	*tmp;
	t_gnl	*tmp_prev;
	t_gnl	*tmp_free;

	tmp_prev = asmb->gnl_last;
	while (tmp_prev->next)
	{
		tmp = tmp_prev->next;
		while (tmp && (ft_strlen(tmp->line) == 0 ||
			tmp->line[skip_first_spaces(tmp->line)] == '\0'))
		{
			tmp_free = tmp;
			tmp = tmp->next;
			free(tmp_free->line);
			free(tmp_free);
		}
		tmp_prev->next = tmp;
		if (tmp_prev->next)
			tmp_prev = tmp_prev->next;
	}
	asmb->gnl_last = asmb->gnl_last->next;
	return (1);
}
