/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 12:28:20 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/13 18:12:07 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	print_arena(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		printf("%.2x ", vm->arena[i].i);
		i++;
		if (i % 64 == 0)
			printf("\n");
	}
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	ft_memset(&vm, 0, sizeof(vm));
	if (parse_args(&vm, argc, argv) &&
		create_player(&vm) && 
		create_cursors(&vm))
	{
		// if (vm.v)
		// 	start_ncurses(&vm);
		// else
		// 	print_arena(&vm);
		printf("game cycle\n");
		game_cycle(&vm);
	}
	// free_all(&vm);
	return (0);
}