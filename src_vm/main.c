/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 12:28:20 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/16 20:01:31 by tpepperm         ###   ########.fr       */
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
	printf("\033[1J\033[;H");
	while (i < MEM_SIZE)
	{
		printf("%.2x ", vm->arena[i].i);
		i++;
		if (i % 64 == 0)
			printf("\n");
	}
	usleep(50000);
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	ft_memset(&vm, 0, sizeof(vm));
	if (parse_args(&vm, argc, argv) &&
		create_player(&vm) &&
		create_cursors(&vm))
	{
		if (vm.v)
			init_ncurses();
		game_cycle(&vm);
	}
	free_all(&vm);
	return (0);
}
