/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork_lfork_aff.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:56:07 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/13 17:56:09 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static void	create_new_cursor(t_vm *vm, t_cursor *cur)
{
	t_cursor	*tmp;
	int			i;

	i = -1;
	tmp = (t_cursor*)malloc(sizeof(t_cursor));
	while (++i < REG_NUMBER)
		tmp->regs[i] = cur->regs[i];
	tmp->cursor_id = vm->cur->cursor_id + 1;
	tmp->carry = cur->carry;
	tmp->live_cycle = cur->live_cycle;
	tmp->op = -1;
	tmp->cycles_left = 0;
	tmp->i = cur->i;
	tmp->op_size = 0;
	tmp->color = cur->color;
	tmp->next = vm->cur;
	vm->cur = tmp;
}

void		op_fork(t_vm *vm, t_cursor *cur, t_arg args[])
{
	create_new_cursor(vm, cur);
	vm->cur->i += (args[0].arg % IDX_MOD) % MEM_SIZE;
}

void		op_lfork(t_vm *vm, t_cursor *cur, t_arg args[])
{
	create_new_cursor(vm, cur);
	vm->cur->i += args[0].arg % MEM_SIZE;
}

void		op_aff(t_cursor *cur, t_arg args[])
{
	printf("%c", (char)cur->regs[args[0].arg - 1]);
}