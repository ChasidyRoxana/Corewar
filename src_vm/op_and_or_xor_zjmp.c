/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and_or_xor_zjmp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 20:03:25 by tpepperm          #+#    #+#             */
/*   Updated: 2020/07/19 14:43:25 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void		op_and(t_vm *vm, t_cursor *cur, t_arg args[])
{
	int		result;
	int		first_arg;
	int		second_arg;

	first_arg = set_arg(vm, cur, args, 0);
	second_arg = set_arg(vm, cur, args, 1);
	result = first_arg & second_arg;
	cur->regs[args[2].arg - 1] = result;
	cur->carry = (result == 0 ? 1 : 0);
	if (vm->d == 2)
		ft_printf("AND: %d & %d -> reg%d = %d\n", first_arg, second_arg,
		args[2].arg - 1, result);
}

void		op_or(t_vm *vm, t_cursor *cur, t_arg args[])
{
	int		result;
	int		first_arg;
	int		second_arg;

	first_arg = set_arg(vm, cur, args, 0);
	second_arg = set_arg(vm, cur, args, 1);
	result = first_arg | second_arg;
	cur->regs[args[2].arg - 1] = result;
	cur->carry = (result == 0 ? 1 : 0);
	if (vm->d == 2)
		ft_printf("OR: %d | %d -> reg%d = %d\n", first_arg, second_arg,
		args[2].arg - 1, result);
}

void		op_xor(t_vm *vm, t_cursor *cur, t_arg args[])
{
	int		result;
	int		first_arg;
	int		second_arg;

	first_arg = set_arg(vm, cur, args, 0);
	second_arg = set_arg(vm, cur, args, 1);
	result = first_arg ^ second_arg;
	cur->regs[args[2].arg - 1] = result;
	cur->carry = (result == 0 ? 1 : 0);
	if (vm->d == 2)
		ft_printf("XOR: %d ^ %d -> reg%d = %d\n", first_arg, second_arg,
		args[2].arg - 1, result);
}

void		op_zjmp(t_vm *vm, t_cursor *cur, t_arg args[])
{
	if (cur->carry)
	{
		vm->arena[cur->i].color = vm->arena[cur->i].prev_color;
		cur->i = check_position(cur->i + (args[0].arg % IDX_MOD));
		cur->op_size = 0;
		if (vm->d == 2)
			ft_printf("ZJMP: arg %d -> %d\n", args[0].arg, cur->i);
	}
	else if (vm->d == 2)
		ft_printf("ZJMP: FAILED\n");
}
