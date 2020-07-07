/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 12:28:20 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/07 21:51:37 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int			check_filename(char *name)
{
	int			length;

	length = ft_strlen(name);
	if (length < 5)
		return (error_vm(ERR_FILE_NAME));
	if (ft_strcmp(&name[length - 4], ".cor") == 0)
		return (1);
	else
		return (error_vm(ERR_FILE_NAME));
}

int		parse_args(char **argv, t_vm *vm) 
{
	int i;
	int	num_players;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-')
			check_flags();
		if (check_filename)
			init_player(); // передать сюда цифру после -n? Или как делать будем?
		num_players += 1;
		if (num_players > MAX_PLAYERS)
			error_vm(ERR_MAX_PLAYERS);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	// memset vm
	// memset арены - арена уже замемсетилась или нет ???
	ft_memset(&vm, 0, sizeof(vm));
	if (argc > 2)
	{
		parse_args(argv, &vm);
	}
	
	// parse_args: 
	// - проверить имя файлов - DONE
	// - проверить, что есть игроки и их кол-во <= MAX_PLAYERS - DONE
	// - обработать флаги (-n, -dump, -v)
	// - записать туда номер игрока, имя, коммент, позицию на арене = проверить имя, коммент, размер 
	// - если все ок, записать код чемпиона в арену
	// - все каретки создать, записать туда номер игроков и все остальные данные (?)
	// - поставить каретки на начало кодов чемпионов
	// - вывести арену (можно сразу в ncurses)
	// parse_args()

	// прописать все команды

	return (0);
}