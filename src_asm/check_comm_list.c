/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_comm_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:49:43 by marvin            #+#    #+#             */
/*   Updated: 2020/07/15 22:20:22 by tpepperm         ###   ########.fr       */
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
		if (tmp->type == T_REG || tmp->type == T_DIR)
			comml->args_type |= (tmp->type << offset);
		else if (tmp->type == T_IND)
			comml->args_type |= (IND_CODE << offset);
		offset -= 2;
		tmp = tmp->next;
	}
}

static int	arg_check_lab2(t_command *comml, char *arg_lab)
{
	int			size;
	t_command	*tmpc;
	t_label		*tmpl;

	tmpc = comml;
	size = 0;
	while (tmpc)
	{
		tmpl = tmpc->label;
		while (tmpl)
		{
			if (!ft_strcmp(tmpl->line, arg_lab))
				return (size);
			tmpl = tmpl->next;
		}
		size += tmpc->size;
		tmpc = tmpc->next;
	}
	return (-1);
}

static int	arg_check_lab(t_command *comml, char *arg_lab)
{
	int			size;
	t_command	*tmpc;
	t_label		*tmpl;

	size = 0;
	tmpc = comml;
	while (tmpc)
	{
		tmpl = tmpc->label;
		while (tmpl)
		{
			if (!ft_strcmp(tmpl->line, arg_lab))
				return (size);
			tmpl = tmpl->next;
		}
		tmpc = tmpc->prev;
		if (tmpc)
			size -= tmpc->size;
	}
	return (1);
}

static int	set_args(t_command *comml)
{
	t_args	*tmpa;
	int		arg;

	tmpa = comml->args;
	while (tmpa)
	{
		if (tmpa->type != T_REG)
		{
			if (tmpa->arg_name && tmpa->arg_name[0] == LABEL_CHAR)
			{
				if ((arg = arg_check_lab(comml, &tmpa->arg_name[1])) > 0)
				{
					if ((arg = arg_check_lab2(comml, &tmpa->arg_name[1])) < 0)
						return (error_args(ERR_LABEL, comml,
						&tmpa->arg_name[1], -1));
				}
				tmpa->arg = arg;
			}
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
		if (!set_args(asmb->comm_last))
			return (0);
		asmb->comm_last = asmb->comm_last->next;
	}
	return (1);
}
