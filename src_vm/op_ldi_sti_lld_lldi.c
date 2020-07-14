/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi_sti_lld_lldi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:28:14 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/14 17:04:42 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	op_ldi(t_vm *vm, t_cursor *cur, t_arg *args)
{
	int reg;
	int address;

	reg = args[2].arg - 1;
	address = 0;
	address += set_arg(vm, cur, args, 0);
	address += set_arg(vm, cur, args, 1);
	address %= IDX_MOD;
	address += cur->i;
	cur->regs[reg] = get_arg(vm, address, 4);
	// printf("LDI: reg%d = %d, address %d\n", reg, cur->regs[reg], address);
}

void	op_sti(t_vm *vm, t_cursor *cur, t_arg *args)
{
	int reg;
	int address; 
	
	reg = args[0].arg - 1;
	address = 0;
	address += set_arg(vm, cur, args, 1);
	address += set_arg(vm, cur, args, 2);
	address %= IDX_MOD;
    address += cur->i;
    write_to_memory(vm, cur, reg, address);
	// printf("STI: reg%d = %d, address %d\n", reg, cur->regs[reg], address);
}

void	op_lld(t_vm *vm, t_cursor *cur, t_arg *args)
{
	int arg;
	int reg;
	int	address;

	arg = -1;
	reg = args[1].arg - 1;
	address = 0;
	if (args[0].type == T_DIR)
		arg = args[0].arg;
	else if (args[0].arg == T_IND)
	{
		address = cur->i + args[0].arg; // отличается с ld только этой строкой
		arg = get_arg(vm, address, 4);
	}
	cur->regs[reg] = arg;
	cur->carry = (arg == 0) ? 1 : 0; // нннада? в ld есть, чекнуть по сабджекту
	// printf("LLD: reg%d = %d\n", reg, arg);
}

void	op_lldi(t_vm *vm, t_cursor *cur, t_arg *args)
{
	int reg;
	int address;

	reg = args[2].arg - 1;
	address = cur->i;
	address += set_arg(vm, cur, args, 0);
	address += set_arg(vm, cur, args, 1);
	cur->regs[reg] = get_arg(vm, address, 4);
	// printf("LLDI: reg%d = %d, address %d\n", reg, cur->regs[reg], address);
}
