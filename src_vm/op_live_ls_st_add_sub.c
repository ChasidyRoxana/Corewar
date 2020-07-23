/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live_ls_st_add_sub.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:32:34 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/22 21:37:38 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	op_live(t_vm *vm, t_cursor *cur, t_arg *args)
{
	int player;

	cur->live_cycle = vm->cycle;
	vm->n_live += 1;
	player = args[0].arg * (-1);
	if (vm->d == 2)
		ft_printf("LIVE: %d\n", player);
	if (player > 0 && player <= vm->n_players)
		vm->winner = player;
}

void	op_ld(t_vm *vm, t_cursor *cur, t_arg *args)
{
	int arg;
	int reg;
	int	address;

	arg = -1;
	reg = args[1].arg - 1;
	address = 0;
	if (args[0].type == T_DIR)
		arg = args[0].arg;
	else if (args[0].type == T_IND)
	{
		address = check_position(cur->i + (args[0].arg % IDX_MOD));
		arg = get_arg(vm, address, 4);
	}
	if (vm->d == 2)
		ft_printf("LD: reg %d, arg %d, address %d\n", reg, arg, address);
	cur->regs[reg] = arg;
	cur->carry = (arg == 0) ? 1 : 0;
}

void	op_st(t_vm *vm, t_cursor *cur, t_arg *args)
{
	int reg;
	int	address;

	address = 0;
	reg = args[0].arg - 1;
	if (args[1].type == T_REG)
	{
		cur->regs[args[1].arg - 1] = cur->regs[reg];
		if (vm->d == 2)
			ft_printf("ST: reg %d -> reg %d\n", reg, args[1].arg - 1);
	}
	else if (args[1].type == T_IND)
	{
		address = check_position(cur->i + (args[1].arg % IDX_MOD));
		write_to_memory(vm, cur, reg, address);
		if (vm->d == 2)
			ft_printf("ST: reg %d -> address %d\n", reg, address);
	}
}

void	op_add(t_vm *vm, t_cursor *cur, t_arg *args)
{
	int arg;
	int	reg_one;
	int	reg_two;
	int	reg_three;

	reg_one = args[0].arg - 1;
	reg_two = args[1].arg - 1;
	reg_three = args[2].arg - 1;
	arg = cur->regs[reg_one] + cur->regs[reg_two];
	cur->regs[reg_three] = arg;
	cur->carry = (arg == 0) ? 1 : 0;
	if (vm->d == 2)
		ft_printf("ADD: reg%d = %d, reg%d = %d, reg%d = %d\n", reg_one,
		cur->regs[reg_one], reg_two, cur->regs[reg_two], reg_three,
		cur->regs[reg_three]);
}

void	op_sub(t_vm *vm, t_cursor *cur, t_arg *args)
{
	int arg;
	int	reg_one;
	int	reg_two;
	int	reg_three;

	reg_one = args[0].arg - 1;
	reg_two = args[1].arg - 1;
	reg_three = args[2].arg - 1;
	arg = cur->regs[reg_one] - cur->regs[reg_two];
	cur->regs[reg_three] = arg;
	cur->carry = (arg == 0) ? 1 : 0;
	if (vm->d == 2)
		ft_printf("SUB: reg%d = %d, reg%d = %d, reg%d = %d\n",
		reg_one, cur->regs[reg_one], reg_two, cur->regs[reg_two],
		reg_three, cur->regs[reg_three]);
}
