/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live_ls_st_add_sub.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:32:34 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/14 17:04:30 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	op_live(t_vm *vm, t_cursor *cur, t_arg *args)
{
	int player;
	
	cur->live_cycle = vm->cycle;
	vm->n_live += 1;
	player = args[0].arg * (-1);
	// printf("LIVE: %d\n", player);
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
	// printf("LD: reg %d, arg %d, address %d\n", reg, arg, address);
	cur->regs[reg] = arg;
	cur->carry = (arg == 0) ? 1 : 0;
}

void	op_st(t_vm *vm, t_cursor *cur, t_arg *args)
{
	int reg;
	int	address;

	address = 0;
	reg = args[0].arg - 1;
	if (args[1].type == T_REG) {
		// printf("ST: reg %d, reg %d\n", args[1].arg - 1, reg);
		cur->regs[args[1].arg - 1] = cur->regs[reg];
	}
	else if (args[1].type == T_IND)
	{
		address = check_position(cur->i + (args[1].arg % IDX_MOD));
		write_to_memory(vm, cur, reg, address);
		// printf("ST: reg %d, address %d\n", args[1].arg - 1, address);
	}
}

void	op_add(t_cursor *cur, t_arg *args)
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
	// printf("ADD: reg%d = %d, reg%d = %d, reg%d = %d\n", reg_one, cur->regs[reg_one], 
		// reg_two, cur->regs[reg_two], reg_three, cur->regs[reg_three]);
}

void	op_sub(t_cursor *cur, t_arg *args)
{
	int arg;
	int	reg_one;
	int	reg_two;
	int	reg_three;
	
	reg_one = args[0].arg - 1;
	reg_two = args[1].arg - 1;
	reg_three = args[2].arg - 1;
	arg = cur->regs[reg_one] - cur->regs[reg_two]; // можно объединить с add, отличие только в этой строке
	cur->regs[reg_three] = arg;
	cur->carry = (arg == 0) ? 1 : 0;
	// printf("SUB: reg%d = %d, reg%d = %d, reg%d = %d\n", reg_one, cur->regs[reg_one], 
		// reg_two, cur->regs[reg_two], reg_three, cur->regs[reg_three]);
}
