/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 21:32:15 by marvin            #+#    #+#             */
/*   Updated: 2020/07/07 21:32:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static int	check_filename(char *name)
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

static int	flag_n(t_vm *vm, int ac, char **av, int *n_arg)
{
	int		i;
	int		num;

	if (*n_arg + 2 >= ac)
		return (error_vm(ERR_FLAG));
	else
	{
		(*n_arg)++;
		// atoi_check какой-нибудь на корректность аргумента
		// if (!atoi_check)
		//	return (0);
		num = ft_atoi(av[*n_arg]);
		if (num < 1 || num > MAX_PLAYERS)
			return (error_vm(ERR_FLAG));
		(*n_arg)++;
		i = 0;
		while (i < MAX_PLAYERS && vm->player[i].file_name != NULL)
			i++;
		if (i >= MAX_PLAYERS)
			return (error_vm(ERR_MAX_PLAYERS));
		if (!check_filename(av[*n_arg]))
			return (0);
		vm->player[i].file_name = ft_strdup(av[(*n_arg)++]);
		vm->player[i].id = num;
		vm->player[i].i = vm->n_players;
		vm->n_players++;
		return (1);
	}
}

static int	flag_dump(t_vm *vm, int ac, char **av, int *n_arg)
{
	if (*n_arg + 2 >= ac || vm->dump != 0)
		return (error_vm(ERR_FLAG));
	else
	{
		(*n_arg)++;
		// atoi_check какой-нибудь на корректность аргумента
		// if (!atoi_check)
		//	return (0);
		vm->dump = ft_atoi(av[(*n_arg)++]);
		return (1);
	}
}

static int	sort_players(t_vm *vm)
{
	int			i;
	t_player	tmp;

	i = -1;
	while (++i < vm->n_players)
	{
		if (vm->player[i].id > vm->n_players)
			return (error_vm(ERR_FLAG));
		if (vm->player[i].id != 0)
		{
			if (vm->player[vm->player[i].id - 1].id == vm->player[i].id &&
				vm->player[vm->player[i].id - 1].i != vm->player[i].i)
				return (error_vm(ERR_FLAG));
			tmp = vm->player[vm->player[i].id - 1];
			vm->player[vm->player[i].id - 1] = vm->player[i];
			vm->player[i] = tmp;
		}
	}
	i = -1;
	while (++i < vm->n_players)
		if (vm->player[i].id == 0)
			vm->player[i].id = i + 1;
	return (1);
}

int			parse_args(t_vm *vm, int ac, char **av)
{
	int		n_arg;
	int		i;

	n_arg = 1;
	if (ac < 2)
		return (error_vm(ERR_FLAG));
	while (n_arg < ac)
	{
		if (!ft_strcmp(av[n_arg], "-v") && vm->v)
			return (0);
		if (!ft_strcmp(av[n_arg], "-dump"))
		{
			if (!flag_dump(vm, ac, av, &n_arg))
				return (0);
		}
		else if (!ft_strcmp(av[n_arg], "-n"))
		{
			if (!flag_n(vm, ac, av, &n_arg))
				return (0);
		}
		else if (!ft_strcmp(av[n_arg], "-v"))
		{
			vm->v = 1;
			n_arg++;
		}
		else
		{
			if (!check_filename(av[n_arg]))
				return (0);
			i = 0;
			while (i < MAX_PLAYERS && vm->player[i].file_name != NULL)
				i++;
			if (i >= MAX_PLAYERS)
				return (error_vm(ERR_MAX_PLAYERS));
			vm->player[i].file_name = ft_strdup(av[n_arg++]);
			vm->player[i].i = vm->n_players;
			vm->n_players++;
		}
	}
	if (!sort_players(vm))
		return (0);
	// printf("dump: %d\nn_pl: %d\nvis: %d\n", vm->dump, vm->n_players, vm->v);
	// for(int j = 0; j < vm->n_players; j++)
	// 	printf(" PL[%d] id: %d, i: %d, filename: %s\n", j, vm->player[j].id,
	// 		vm->player[j].i, vm->player[j].file_name);
	return (1);
}
