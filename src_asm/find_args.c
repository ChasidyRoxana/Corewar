/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 15:21:30 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/24 00:48:20 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			new_args(t_command *command)
{
	t_args *tmp;

	tmp = command->args;
	if (command->args == NULL)
	{
		if (!(command->args = (t_args*)malloc(sizeof(t_args))))
			return (error_common(ERR_MALLOC));
		tmp = command->args;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_args*)malloc(sizeof(t_args))))
			return (error_common(ERR_MALLOC));
		tmp = tmp->next;
	}
	tmp->type = 0;
	tmp->arg = 0;
	tmp->arg_name = NULL;
	tmp->next = NULL;
	return (1);
}

int			write_arg(t_asm *asmb, t_args *tmp, int *i, int index_op)
{
	int last;
	int err;

	err = 0;
	if ((OP(index_op).args[asmb->comm_last->num_args] & tmp->type) == 0)
		return (error_args(ERR_ARG, asmb->comm_last, 0, (*i)));
	last = *i;
	if (!check_numeric(asmb, &err, i, &last))
		return (0);
	if (last == *i || (!is_separator(asmb->gnl_last->line[*i]) &&
		!is_comment(asmb->gnl_last->line[*i])) || err == 0)
		return (error_line(ERR_LEXICAL, asmb->gnl_last, (*i)));
	if (!(tmp->arg_name = ft_strnew(*i - last)))
		return (error_common(ERR_MALLOC));
	ft_strncpy(tmp->arg_name, &asmb->gnl_last->line[last], (*i - last));
	asmb->comm_last->num_args++;
	return (1);
}

int			double_check_args(t_asm *asmb, int *i)
{
	while (is_space(asmb->gnl_last->line[*i]))
		(*i)++;
	if (!asmb->gnl_last->line[*i])
		return (1);
	if (is_comment(asmb->gnl_last->line[*i]))
		return (1);
	else if (asmb->gnl_last->line[*i] == SEPARATOR_CHAR)
	{
		(*i)++;
		while (is_space(asmb->gnl_last->line[*i]))
			(*i)++;
		if (!asmb->gnl_last->line[*i])
			return (error_line(ERR_SYNTAX, asmb->gnl_last, (*i)));
	}
	else
		return (error_line(ERR_SYNTAX, asmb->gnl_last, (*i)));
	return (-1);
}

int			proceed_args(t_asm *asmb, t_args *tmp, int *i, int index_op)
{
	if (asmb->gnl_last->line[*i] == 'r')
	{
		(*i)++;
		tmp->type = T_REG;
		if (!write_arg(asmb, tmp, i, index_op))
			return (0);
		tmp->arg = ft_atoi(tmp->arg_name);
		if (!(tmp->arg >= 1 && tmp->arg <= REG_NUMBER) ||
			!(check_atoi(tmp->arg_name)))
			return (error_line(ERR_REG, asmb->gnl_last, (*i)));
	}
	else
	{
		if (asmb->gnl_last->line[*i] == '%')
		{
			(*i)++;
			tmp->type = T_DIR;
		}
		else if (asmb->gnl_last->line[*i] == ':' ||
		is_numeric(asmb->gnl_last->line[*i]) || asmb->gnl_last->line[*i] == '-')
			tmp->type = T_IND;
		if (!write_arg(asmb, tmp, i, index_op))
			return (0);
	}
	return (1);
}

int			find_args(t_asm *asmb, int i, int index_op)
{
	t_args	*tmp;
	int		res;

	tmp = NULL;
	while (is_space(asmb->gnl_last->line[i]))
		i++;
	while (asmb->gnl_last->line[i])
	{
		if (asmb->comm_last->num_args == OP(index_op).nb_arg)
			return (error_args(ERR_MAX_ARG, asmb->comm_last, 0, i));
		if (!new_args(asmb->comm_last))
			return (0);
		tmp = asmb->comm_last->args;
		while (tmp->next)
			tmp = tmp->next;
		if (is_args(asmb->gnl_last->line[i]))
		{
			res = parse_args(asmb, tmp, &i, index_op);
			if (res == 0 || res == 1)
				return (res);
		}
		else
			return (error_line(ERR_SYNTAX, asmb->gnl_last, i));
	}
	return (error_args(ERR_NO_ARGS, asmb->comm_last, 0, i));
}
