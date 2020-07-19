/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 16:16:07 by marvin            #+#    #+#             */
/*   Updated: 2020/07/19 13:49:03 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int			count_size_arg_code(t_vm *vm, int op, int i)
{
	int j;
	int res;
	int size;
	int arg_code;

	i = i % MEM_SIZE;
	j = 6;
	res = 0;
	size = 2;
	arg_code = vm->arena[i].i;
	while (j > 0 && ((arg_code >> j) & 3) != 0)
	{
		res = (arg_code >> j) & 3;
		if (res == 1)
			size += 1;
		else if (res == 3)
			size += 2;
		else if (res == 2)
			size += (OP(op - 1).t_dir_size == 1) ? 2 : 4;
		j -= 2;
	}
	return (size);
}

int			count_size(t_vm *vm, int op, int i)
{
	int	size;

	size = 1;
	if (OP(op - 1).type_arg_code == 0)
	{
		if (OP(op - 1).args[0] == T_REG)
			size += 1;
		else if (OP(op - 1).args[0] == T_IND)
			size += 2;
		else if (OP(op - 1).args[0] == T_DIR)
			size += (OP(op - 1).t_dir_size == 1) ? 2 : 4;
	}
	else
		size = count_size_arg_code(vm, op, i);
	return (size);
}

void		cycles_less_zero(t_vm *vm, t_cursor *tmp)
{
	tmp->op = vm->arena[tmp->i].i;
	if (tmp->op >= 1 && tmp->op <= 16)
	{
		tmp->cycles_left = OP(tmp->op - 1).cycle;
		tmp->op_size = count_size(vm, tmp->op, tmp->i + 1);
	}
	else
		tmp->op_size = 1;
}

/*
** каретки:
** 1. устанавливаем код операции
** 2. уменьшить количество циклов до исполнения
** 3. выполнить операцию
*/

int			cursor_op(t_vm *vm)
{
	t_cursor	*tmp;

	tmp = vm->cur;
	while (tmp)
	{
		if (tmp->cycles_left <= 0)
			cycles_less_zero(vm, tmp);
		tmp->cycles_left--;
		if (tmp->cycles_left <= 0)
		{
			if (tmp->op >= 1 && tmp->op <= 16)
				check_op(vm, tmp);
			vm->arena[tmp->i].color = vm->arena[tmp->i].prev_color;
			tmp->i = check_position(tmp->i + tmp->op_size);
			vm->arena[tmp->i].color = tmp->color;
		}
		tmp = tmp->next;
	}
	return (1);
}
