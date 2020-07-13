/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 19:56:51 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/13 12:59:06 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int			check_position(int pos)
{
	// if (pos >= MEM_SIZE)
		return (pos % MEM_SIZE);
	// else
		// return (pos);
}

int			get_arg(t_vm *vm, int i, int size)
{
	int j;
	int arg;

	j = -1;
	arg = 0;
	while (++j < size)
		arg |= vm->arena[i++ % MEM_SIZE].i << ((size - j - 1) * 8);
		// разобраться с делением на MEM_SIZE
	if ((arg >> (size * 8 - 1)) & 1)
	{
		j = size * 8;
		while (j < 32)
			arg |= 1 << j++;
	}
	return (arg);
}

int         write_args(t_vm *vm, t_cursor *cur, t_arg *args, int num_args)
{
	int j;
	int pos;
	int size;

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

int         write_types(t_vm *vm, t_cursor *cur, t_arg *args, int num_args)
{
	int j;
	int pos;
	int type;
	int bytes;

	j = -1;
	type = 0;
	bytes = 6;
	pos = check_position(cur->i + 1);
	if (OP(cur->op - 1).type_arg_code == 1)
	{
		while (bytes >= 0)
		{
			// нужные аргументы записываются, остальное проверется, что там нет никаких лишних битов
			if (++j < num_args)
			{
				if ((type = ((vm->arena[pos].i >> bytes) & 3)) == 0)
					return (0);
				if (type == IND_CODE)
					type = T_IND;
				if ((type & OP(cur->op - 1).args[j]) == 0)
					return (0);
				args[j].type = type;
			}
			else
				if (((vm->arena[pos].i >> bytes) & 3) != 0)
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
	t_arg   args[OP(cur->op - 1).nb_arg];
    int 	num_args;

	num_args = OP(cur->op - 1).nb_arg;
	if (!write_types(vm, cur, args, num_args))
		return (0);
	if (!write_args(vm, cur, args, num_args))
		return (0);
	// отправить в свою команду
	// send_to_op(cur);

	// вывод аргументов для проверки
	int i = -1;
	while (++i < num_args)
		printf("TYPE: %d ARG: %d\n", args[i].type, args[i].arg);
	
	return (1);
}
