/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_corewar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 20:17:48 by tpepperm          #+#    #+#             */
/*   Updated: 2020/07/20 20:28:06 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	introduce_players(t_vm *vm)
{
	int i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < vm->n_players)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
		vm->player[i].champ_size, vm->player[i].name, vm->player[i].comment);
		i++;
	}
}

void	print_arena(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%.2x ", vm->arena[i].i);
		i++;
		if (i % 64 == 0)
			ft_printf("\n");
	}
}

void	declare_winner(t_vm *vm)
{
	ft_printf("Contestant %d, \"%s\", has won !\n",
		vm->winner, vm->player[vm->winner - 1].name);
}
