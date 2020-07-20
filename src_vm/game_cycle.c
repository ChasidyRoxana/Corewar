/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:52:33 by marvin            #+#    #+#             */
/*   Updated: 2020/07/20 22:26:18 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static int	check_cursor(t_vm *vm, int *cycle)
{
	t_cursor	*tmp;
	t_cursor	*tmp2;

	tmp = vm->cur;
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
		*game = 0;
	if (vm->d)
		ft_printf("~ Checkup ~ live: %d, checks: %d, cycles_to_die %d -> ",
		vm->n_live, vm->n_check, vm->cycles_to_die);
	if (vm->n_live >= NBR_LIVE || vm->n_check == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->n_check = 1;
	}
	else
		vm->n_check++;
	if (vm->d)
		ft_printf("%d%s ~\n", vm->cycles_to_die, (*game ? "" : " game over"));
	*cycle = 0;
	vm->n_live = 0;
}

void		finish_game(t_vm *vm)
{
	if (vm->v && !vm->dump && !vm->d)
		print_ncurses(vm, 1, 0);
	if (vm->dump)
		print_arena(vm);
	else if (!vm->v)
		declare_winner(vm);
	if (vm->d)
		ft_printf("~~~END!  Cycle: %d\n", vm->cycle);
}

int			game_cycle(t_vm *vm)
{
	int	play;
	int	cycle;

	play = 1;
	cycle = 1;
	while (play || (vm->dump != 0 && vm->cycle <= vm->dump))
	{
		if (vm->v && !vm->dump && !vm->d)
			print_ncurses(vm, 0, 0);
		cursor_op(vm);
		if (cycle == vm->cycles_to_die || vm->cycles_to_die <= 0)
			check_up(vm, &cycle, &play);
		cycle++;
		vm->cycle++;
	}
	vm->cycle--;
	finish_game(vm);
	return (1);
}
