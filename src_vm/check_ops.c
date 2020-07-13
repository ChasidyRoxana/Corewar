/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 19:56:51 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/13 12:14:47 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

// проверка выхода за 4096 (MEM_SIZE)
int			check_position(int pos)
{
	if (pos >= MEM_SIZE)
		return (pos % MEM_SIZE);
	else
		return (pos);
}

// запись аргумента из disasm
int			get_arg(t_vm *vm, int i, int size)
{
	int j;
	int arg;

	j = -1;
	arg = 0;
	while (++j < size)
		arg |= vm->arena[i++].i << ((size - j - 1) * 8);
	if ((arg >> (size * 8 - 1)) & 1)
	{
		j = size * 8;
		while (j < 32)
			arg |= 1 << j++;
	}
	return (arg);
}

int         write_args(t_vm *vm, t_cursor *cur, int num_args)
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
        if (cur->args[j].type == REG_CODE)
            size = 1; // макрос?
        else if (cur->args[j].type == IND_CODE)
            size = 2; // макрос?
        else if (cur->args[j].type == DIR_CODE)
            size = (OP(cur->op - 1).t_dir_size == 1) ? 2 : 4; // макросы?
        cur->args[j].arg = get_arg(vm, pos, size);
		// проверка регистров
        if (cur->args[j].type == REG_CODE && (cur->args[j].arg <= 0 ||
            cur->args[j].arg > REG_NUMBER))
            return (0);
		pos = check_position(pos + size);
    }
    return (1);
}

int         write_types(t_vm *vm, t_cursor *cur, int num_args)
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
        while (++j < num_args)
        {
			// проверка, если в коде аргументов меньше аргументов, чем должно быть для команды
            if (bytes <= 0 || ((vm->arena[pos].i >> bytes) & 3) == 0)
				return (0);
			type = (vm->arena[pos].i >> bytes) & 3;
			cur->args[j].type = type;
            bytes -= 2;
        }
        // надо после вайла проверить, что считали все аргументы из типа аргументов?
        // if !(((vm->arena[cur->i + 1].i >> bytes) & 3) == 0) -> return (0)
    }
    else 
        while (++j < num_args)
            cur->args[j].type = OP(cur->op - 1).args[j];
    return (1);
}

int			check_op(t_vm *vm, t_cursor *cur)
{
	int num_args;
    // сделать статическим cur->args !!!
	num_args = OP(cur->op - 1).nb_arg;
	// выделяем память на кол-во аргументов в операции
	if (!(cur->args = (t_arg*)malloc(sizeof(t_arg) * num_args)))
		return (error_vm(ERR_MALLOC));
	// смотрим код типов аргументов, записываем тип каждого аргумента в лист
	if (!write_types(vm, cur, num_args))
		return (0);
    // считываем нужное количество байтов на аргумент, записываем каждый
    if (!write_args(vm, cur, num_args))
		return (0);
	// отправить в свою команду
	// send_to_op(cur);

	// вывод аргументов для проверки
    int i = -1;
    while (++i < num_args)
        printf("TYPE: %d ARG: %d\n", cur->args[i].type, cur->args[i].arg);
    
	return (1);
}
