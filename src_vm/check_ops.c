/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 19:56:51 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/19 13:35:19 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int			write_args(t_vm *vm, t_cursor *cur, t_arg *args, int num_args)
{
	int		j;
	int		pos;
	int		size;

	j = -1;
	size = 0;
	pos = check_position(cur->i + 1);
	if (OP(cur->op - 1).type_arg_code == 1)
		pos = check_position(pos + 1);
	while (++j < num_args)
	{
		if (args[j].type == T_REG)
			size = 1;
		else if (args[j].type == T_IND)
			size = 2;
		else if (args[j].type == T_DIR)
			size = (OP(cur->op - 1).t_dir_size == 1) ? 2 : 4;
		args[j].arg = get_arg(vm, pos, size);
		if (args[j].type == T_REG && (args[j].arg <= 0 ||
			args[j].arg > REG_NUMBER))
			return (0);
		pos = check_position(pos + size);
	}
	return (1);
}

int			arg_to_type(t_vm *vm, t_cursor *cur, int bytes, int j)
{
	int	pos;
	int type;

	type = 0;
	pos = check_position(cur->i + 1);
	if ((type = ((vm->arena[pos].i >> bytes) & 3)) == 0)
		return (0);
	if (type == IND_CODE)
		type = T_IND;
	if ((type & OP(cur->op - 1).args[j]) == 0)
		return (0);
	return (type);
}

int			write_types(t_vm *vm, t_cursor *cur, t_arg *args, int num_args)
{
	int		j;
	int		pos;
	int		bytes;

	j = -1;
	bytes = 6;
	pos = check_position(cur->i + 1);
	if (OP(cur->op - 1).type_arg_code == 1)
	{
		while (bytes >= 0)
		{
			if (++j < num_args)
			{
				if ((args[j].type = arg_to_type(vm, cur, bytes, j)) == 0)
					return (0);
			}
			else if (((vm->arena[pos].i >> bytes) & 3) != 0)
				return (0);
			bytes -= 2;
		}
	}
	else
		while (++j < num_args)
			args[j].type = OP(cur->op - 1).args[j];
	return (1);
}

int			check_op(t_vm *vm, t_cursor *cur)
{
	t_arg	args[OP(cur->op - 1).nb_arg];
	int		num_args;

	num_args = OP(cur->op - 1).nb_arg;
	if (!write_types(vm, cur, args, num_args))
		return (0);
	if (!write_args(vm, cur, args, num_args))
		return (0);
	send_to_op(vm, cur, args);
	return (1);
}
