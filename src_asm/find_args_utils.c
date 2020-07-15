/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 23:58:30 by tpepperm          #+#    #+#             */
/*   Updated: 2020/07/16 00:16:04 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		is_numeric(char c)
{
	return (c >= '0' && c <= '9');
}

int		check_numeric(t_asm *asmb, int *err, int *i, int *last)
{
	if (asmb->gnl_last->line[*i] == '-')
	{
		(*i)++;
		if (!(is_numeric(asmb->gnl_last->line[*i])))
			return (error_line(ERR_SYNTAX, asmb->gnl_last, (*i)));
	}
	if (is_numeric(asmb->gnl_last->line[*i]))
		while (is_numeric(asmb->gnl_last->line[*i]))
		{
			(*i)++;
			*err = 1;
		}
	else if (asmb->gnl_last->line[*i] == ':')
	{
		*last = *i;
		while (asmb->gnl_last->line[++(*i)] &&
		ft_strchr(LABEL_CHARS, asmb->gnl_last->line[*i]))
			*err = 1;
	}
	return (1);
}

int		parse_args(t_asm *asmb, t_args *tmp, int *i, int index_op)
{
	int check;

	check = -1;
	if (!proceed_args(asmb, tmp, i, index_op))
		return (0);
	if ((check = double_check_args(asmb, i)) == 0)
		return (0);
	else if (check == 1)
	{
		if (asmb->comm_last->num_args != OP(index_op).nb_arg)
			return (error_args(ERR_MIN_ARG, asmb->comm_last, 0, *i));
		return (1);
	}
	return (-1);
}
