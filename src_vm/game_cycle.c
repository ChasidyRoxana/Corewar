/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:52:33 by marvin            #+#    #+#             */
/*   Updated: 2020/07/19 15:18:45 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static int	check_cursor(t_vm *vm, int *cycle)
{
	t_cursor	*tmp;
	t_cursor	*tmp2;

	tmp = vm->cur;
	printf("vm->cycle: %d - tmp->live_cycle: %d = %d, cycle: %d\n",
	vm->cycle, tmp->live_cycle, vm->cycle - tmp->live_cycle, *cycle);
	while (tmp)
	{
		if (vm->cycle - tmp->live_cycle >= *cycle)
		{
			tmp2 = vm->cur;
			if (tmp2 == tmp)
				vm->cur = vm->cur->next;
			else
			{
				while (tmp2->next != tmp && tmp2->next)
					tmp2 = tmp2->next;
				tmp2->next = tmp->next;
			}
			// printf("delete %d cursor\n", tmp->cursor_id);
			vm->arena[tmp->i].color = vm->arena[tmp->i].prev_color;
			free(tmp);
			tmp = vm->cur;
		}
		else
			tmp = tmp->next;
	}
	return (1);
}

/*
** если vm->n_live >= NBR_LIVE уменьшаем vm->cycle_to_die на CYCLE_DELTA
** если после проверки vm->cycle_to_die не уменьшился на CYCLE_DELTA,
** то vm->n_check++
** если vm->n_check == MAX_CHECKS уменьшаем vm->cycle_to_die на CYCLE_DELTA
** если кареток больше нет play = 0
*/

static void	check_up(t_vm *vm, int *cycle, int *game)
{
	check_cursor(vm, cycle);
	if (!vm->cur)
	{
		*game = 0;
		return ;
	}
	// printf("=====\nvm->n_live: %d, vm->cycles_to_die %d -> ",
	// vm->n_live, vm->cycles_to_die);
	if (vm->n_live >= NBR_LIVE || vm->n_check == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->n_check = 1;
	}
	else
		vm->n_check++;
	// printf("%d, vm->n_check: %d\n=====\n", vm->cycles_to_die, vm->n_check);
	*cycle = 0;
	vm->n_live = 0;
}

void	declare_winner(t_vm *vm)
{
	printf("Contestant %d, \"%s\", has won !\n", 
		vm->winner, vm->player[vm->winner - 1].name);
}

int			game_cycle(t_vm *vm)
{
	int	play;
	int	cycle;

	play = 1;
	cycle = 1;
	vm->n_check = 1;
	vm->cycle = 1;
	vm->cycles_to_die = CYCLE_TO_DIE;
	while (play || (vm->dump != 0 && vm->cycle <= vm->dump))
	{
		if (vm->v)
			print_ncurses(vm, 0);
		cursor_op(vm);
		if (cycle == vm->cycles_to_die || vm->cycles_to_die <= 0)
			check_up(vm, &cycle, &play);
		cycle++;
		vm->cycle++;
	}
	vm->cycle--;
	if (vm->v && !vm->dump)
	{
		print_ncurses(vm, 1);
		// endwin();
	}
	if (vm->dump)
		print_arena(vm);
	else
		declare_winner(vm);
	printf("END\nvm->cycle: %d\n", vm->cycle);
	return (1);
}
