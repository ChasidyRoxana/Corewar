/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 15:35:42 by marvin            #+#    #+#             */
/*   Updated: 2020/07/19 14:44:01 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static void	send_to_op2(t_vm *vm, t_cursor *cur, t_arg args[])
{
	if (cur->op == 10)
		op_ldi(vm, cur, args);
	else if (cur->op == 11)
		op_sti(vm, cur, args);
	else if (cur->op == 12)
		op_fork(vm, cur, args);
	else if (cur->op == 13)
		op_lld(vm, cur, args);
	else if (cur->op == 14)
		op_lldi(vm, cur, args);
	else if (cur->op == 15)
		op_lfork(vm, cur, args);
	else if (cur->op == 16)
		op_aff(vm, cur, args);
}

void		send_to_op(t_vm *vm, t_cursor *cur, t_arg args[])
{
	if (vm->d == 2)
		ft_printf("Cursor %d: ", cur->cursor_id);
	if (cur->op == 1)
		op_live(vm, cur, args);
	else if (cur->op == 2)
		op_ld(vm, cur, args);
	else if (cur->op == 3)
		op_st(vm, cur, args);
	else if (cur->op == 4)
		op_add(vm, cur, args);
	else if (cur->op == 5)
		op_sub(vm, cur, args);
	else if (cur->op == 6)
		op_and(vm, cur, args);
	else if (cur->op == 7)
		op_or(vm, cur, args);
	else if (cur->op == 8)
		op_xor(vm, cur, args);
	else if (cur->op == 9)
		op_zjmp(vm, cur, args);
	else
		send_to_op2(vm, cur, args);
}
