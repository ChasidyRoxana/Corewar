/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:52:33 by marvin            #+#    #+#             */
/*   Updated: 2020/07/13 18:13:57 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static int	check_cursor(t_vm *vm, int *cycle)
{
	t_cursor	*tmp;
	t_cursor	*tmp2;

	tmp = vm->cur;
	// printf("vm->cycle: %d, tmp->live_cycle: %d, cycle: %d\n", vm->cycle, tmp->live_cycle, *cycle);
	while (tmp)
	{
		if (vm->cycle - tmp->live_cycle >= *cycle)
		{
			tmp2 = vm->cur;
			if (tmp2 == tmp)
				vm->cur = tmp->next;
			else
			{
				while (tmp2->next != tmp && tmp2->next)
					tmp2 = tmp2->next;
				tmp2->next = tmp->next;
			}
			printf("delete %d cursor\n", tmp->cursor_id);
			free(tmp);
			tmp = vm->cur;
		}
		else
			tmp = tmp->next;
	}
	return (1);
}

static int	check_up(t_vm *vm, int *cycle, int *game)
{
	//	если vm->n_live >= NBR_LIVE уменьшаем vm->cycle_to_die на CYCLE_DELTA
	//	если после проверки vm->cycle_to_die не уменьшился на CYCLE_DELTA, то vm->n_check++
	//	если vm->n_check == MAX_CHECKS уменьшаем vm->cycle_to_die на CYCLE_DELTA
	//	если кареток больше нет play = 0
	check_cursor(vm, cycle);
	if (!vm->cur)
		*game = 0;
	printf("vm->cycles_to_die %d -> ", vm->cycles_to_die);
	if (vm->n_live >= NBR_LIVE || vm->n_check == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->n_check = 1;
	}
	else
		vm->n_check++;
	printf("%d, vm->n_check: %d\n", vm->cycles_to_die, vm->n_check);
	*cycle = 0;
	vm->n_live = 0;
	return (1);
}

int			game_cycle(t_vm *vm)
{
	int	play;
	int	cycle;
	
	play = 1;
	cycle = 1;
	vm->cycle = 1;
	vm->cycles_to_die = CYCLE_TO_DIE;
	while (play)
	{
	//	визуализация, если vm->v == 1
	//	
		cursor_op(vm);
		if (cycle == vm->cycles_to_die || vm->cycles_to_die <= 0)
			check_up(vm, &cycle, &play);
		cycle++;
		vm->cycle++;
	}
	vm->cycle--;
	// финальная визуализация
	printf("END\nvm->cycle: %d\n", vm->cycle);
	return(1);
}
