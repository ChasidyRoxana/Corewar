/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 15:30:15 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/13 18:44:15 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		malloc_cursor(t_vm *vm)
{
	t_cursor *tmp;

	if (!(tmp = (t_cursor*)malloc(sizeof(t_cursor))))
		return (error_vm(ERR_MALLOC));
	ft_memset(&tmp->regs, 0, sizeof(tmp->regs));
	tmp->cursor_id = 0;
	tmp->carry = 0;
	tmp->live_cycle = 0;
	tmp->op = 0;
	tmp->cycles_left = 0;
	tmp->i = 0;
	tmp->op_size = 0;
	if (!(vm->cur))
		tmp->next = NULL;
	else
		tmp->next = vm->cur;
	vm->cur = tmp;
	return (1);
}

int		create_cursors(t_vm *vm) 
{
	int i;

	i = 0;
	while (i < vm->n_players)
	{
		// выделить память
		if (!malloc_cursor(vm))
			return (0);
		vm->cur->regs[0] = vm->player[i].id * (-1); // номер игрока со знаком минус
		vm->cur->cursor_id = i + 1; // id каретки

		vm->cur->cycles_left = 0;
		vm->cur->i = vm->player[i].i; // текущая позиция каретки
		
		// printf
		// printf("PLAYER: %d\nCURSOR: %d\nOP: %d\nCYCLES: %d\ni: %d\nOP SIZE: %d\n\n", vm->cur->regs[0], vm->cur->cursor_id, vm->cur->op, 
		// vm->cur->cycles_left, vm->cur->i, vm->cur->op_size);
		
		i++;
	}
	return (1);
}
