/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:52:33 by marvin            #+#    #+#             */
/*   Updated: 2020/07/08 20:23:11 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int			game_cycle(t_vm *vm)
{
	if (vm)
		vm = NULL;//
	// int	play = 1;
	// int	cycle = 0;
	// while(play)
	// {
	//	визуализация, если vm->v == 1
	//	cycle++ пока <= (или < ?) vm->cycles_to_die, когда будет == првоерка
	//	если vm->n_live >= NBR_LIVE уменьшаем vm->cycle_to_die на CYCLE_DELTA
	//	если после проверки vm->cycle_to_die не уменьшился на CYCLE_DELTA, то vm->n_check++
	//	если vm->n_check == MAX_CHECKS уменьшаем vm->cycle_to_die на CYCLE_DELTA
	//	если кареток больше нет play = 0
	//	
	//	каретки:
	//	1. устанавливаем код операции
	//	2. уменьшить количество циклов до исполнения
	//	3. выполнить операцию
	//	
	//	vm->cycle++;
	// }
	return(1);
}
