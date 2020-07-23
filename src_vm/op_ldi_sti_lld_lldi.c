/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi_sti_lld_lldi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:28:14 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/20 20:27:17 by tpepperm         ###   ########.fr       */
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
	cur->regs[reg] = get_arg(vm, check_position(address), 4);
	if (vm->d == 2)
		ft_printf("LDI: address %d, reg%d = %d\n", address, reg,
		cur->regs[reg]);
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
	write_to_memory(vm, cur, reg, check_position(address));
	if (vm->d == 2)
		ft_printf("STI: address %d, reg%d = %d\n", address, reg,
		cur->regs[reg]);
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
		address = check_position(cur->i + args[0].arg);
		arg = get_arg(vm, address, 4);
	}
	cur->regs[reg] = arg;
	cur->carry = (arg == 0) ? 1 : 0;
	if (vm->d == 2)
		ft_printf("LLD: reg%d = %d\n", reg, arg);
}

void	op_lldi(t_vm *vm, t_cursor *cur, t_arg *args)
{
	int arg;
	int reg;
	int address;

	reg = args[2].arg - 1;
	address = cur->i;
	address += set_arg(vm, cur, args, 0);
	address += set_arg(vm, cur, args, 1);
	arg = get_arg(vm, check_position(address), 4);
	cur->regs[reg] = arg;
	cur->carry = (arg == 0) ? 1 : 0;
	if (vm->d == 2)
		ft_printf("LLDI: address %d, reg%d = %d\n", address, reg,
		cur->regs[reg]);
}
