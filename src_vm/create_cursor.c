/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 15:30:15 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/09 15:41:57 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		malloc_cursor(t_vm *vm)
{
	t_cursor *tmp;

	if (!(tmp = (t_cursor*)malloc(sizeof(t_cursor))))
		return (error_vm(ERR_MALLOC));
	tmp->player_id = 0;
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

int		count_size_arg_code(t_vm *vm, int i)
{
	int j;
	int res;
	int size; 
	int arg_code;
	
	j = 6;
	res = 0;
	size = 2; // 1 байт на код операции + 1 байт на код аргументов
	arg_code = vm->arena[vm->player[i].i + 1].i;
	while (j > 0 && ((arg_code >> j) & 3) != 0)
	{
		res = (arg_code >> j) & 3;
		if (res == 1)
			size += 1;
		else if (res == 3)
			size += 2;
		else if (res == 2)
			size += (OP(vm->cur->op - 1).t_dir_size == 1) ? 2 : 4;
		j -= 2;
	}
	return (size);
}

int		count_size(t_vm *vm, int i)
{
	int	size;

	size = 1; // 1 байт на код операции
	if (OP(vm->cur->op - 1).type_arg_code == 0)
	{
		if (OP(vm->cur->op - 1).args[0] == T_REG)
			size += 1;
		else if (OP(vm->cur->op - 1).args[0] == T_IND)
			size += 2;
		else if (OP(vm->cur->op - 1).args[0] == T_DIR)
			size += (OP(vm->cur->op - 1).t_dir_size == 1) ? 2 : 4;
	}
	else 
		size = count_size_arg_code(vm, i);
	return (size);
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
		vm->cur->player_id = vm->player[i].id; // id игрока - можно убрать
		vm->cur->cursor_id = i + 1; // id каретки
		vm->cur->op = (unsigned int)vm->arena[vm->player[i].i].i; // нннада unsigned int? считываем 1 байт с арены
		vm->cur->cycles_left = OP(vm->cur->op - 1).cycle; // смотрим циклы до исполнения по op.c в зависимости от команды
		vm->cur->i = vm->player[i].i; // текущая позиция каретки
		vm->cur->op_size = count_size(vm, i); // размер операции, на которой стоит каретка
		
		// printf
		printf("PLAYER: %d\nCURSOR: %d\nOP: %d\nCYCLES: %d\ni: %d\nOP SIZE: %d\n\n", vm->cur->regs[0], vm->cur->cursor_id, vm->cur->op, 
		vm->cur->cycles_left, vm->cur->i, vm->cur->op_size);
		
		i++;
	}
	return (1);
}
