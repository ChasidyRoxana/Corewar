/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 12:28:20 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/19 15:18:29 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static void	free_all(t_vm *vm)
{
	t_cursor	*tmp;

	while (vm->cur)
	{
		tmp = vm->cur;
		vm->cur = vm->cur->next;
		free(tmp);
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

int		main(int argc, char **argv)
{
	t_vm	vm;

	ft_memset(&vm, 0, sizeof(vm));
	vm.n_check = 1;
	vm.cycle = 1;
	vm.cycles_to_die = CYCLE_TO_DIE;
	if (parse_args(&vm, argc, argv) &&
		create_player(&vm) &&
		create_cursors(&vm))
	{
		// if (vm.v && !vm.dump && !vm.d)
		// 	init_ncurses();
		introduce_players(&vm);
		game_cycle(&vm);
	}
	free_all(&vm);
	return (0);
}
