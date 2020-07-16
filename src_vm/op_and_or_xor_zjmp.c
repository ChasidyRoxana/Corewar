/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and_or_xor_zjmp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 20:03:25 by tpepperm          #+#    #+#             */
/*   Updated: 2020/07/16 20:03:55 by tpepperm         ###   ########.fr       */
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
	// printf("AND: reg%d = %d\n", args[2].arg - 1, result);
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
	// printf("OR: reg%d = %d\n", args[2].arg - 1, result);
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
	// printf("XOR: reg%d = %d\n", args[2].arg - 1, result);
}

void		op_zjmp(t_cursor *cur, t_arg args[])
{
	if (cur->carry)
	{
		cur->i = check_position(args[0].arg);
		cur->op_size = 0;
		// printf("ZJMP %d\n", cur->i);
	}
	// else
	// 	printf("ZJMP FAILED\n");
}
