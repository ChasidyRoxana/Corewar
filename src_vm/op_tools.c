/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 20:07:32 by tpepperm          #+#    #+#             */
/*   Updated: 2020/07/19 14:10:57 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		check_position(int pos)
{
	if (pos < 0)
		return (MEM_SIZE + (pos % MEM_SIZE));
	return (pos % MEM_SIZE);
}

int		get_arg(t_vm *vm, int i, int size)
{
	int j;
	int arg;

	j = -1;
	arg = 0;
	while (++j < size)
		arg |= vm->arena[check_position(i++)].i << ((size - j - 1) * 8);
	if ((arg >> (size * 8 - 1)) & 1)
	{
		j = size * 8;
		while (j < 32)
			arg |= 1 << j++;
	}
	return (arg);
}

void	write_to_memory(t_vm *vm, t_cursor *cur, int reg, int address)
{
	int				i;
	unsigned int	num;

	i = 4;
	num = cur->regs[reg];
	while (--i >= 0)
	{
		vm->arena[check_position(address + i)].i = num % 256;
		if (vm->arena[check_position(address + i)].color % 2 != 0 ||
			vm->arena[check_position(address + i)].color == 0)
			vm->arena[check_position(address + i)].color = cur->color - 1;
		vm->arena[check_position(address + i)].prev_color = cur->color - 1;
		num /= 256;
	}
}

/*
** возвращает значение регистра/дира/значение по инд(%IDX_MOD)
*/

int		set_arg(t_vm *vm, t_cursor *cur, t_arg args[], int i)
{
	if (args[i].type == T_REG)
		return (cur->regs[args[i].arg - 1]);
	else if (args[i].type == T_DIR)
		return (args[i].arg);
	else
		return (get_arg(vm, cur->i + (args[i].arg % IDX_MOD), 4));
}
