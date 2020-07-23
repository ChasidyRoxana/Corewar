/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 21:32:15 by marvin            #+#    #+#             */
/*   Updated: 2020/07/21 22:52:15 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

static int	flag_n(t_vm *vm, int ac, char **av, int *n_arg)
{
	int		num;

	num = 0;
	if (*n_arg + 2 >= ac)
		return (error_vm(ERR_FLAG));
	else
	{
		(*n_arg)++;
		if (!check_atoi(av[*n_arg]))
			return (error_vm(ERR_FLAG));
		num = ft_atoi(av[*n_arg]);
		(*n_arg)++;
		if (num < 1 || num > MAX_PLAYERS)
			return (error_vm(ERR_FLAG));
		if (vm->n_players >= MAX_PLAYERS)
			return (error_vm(ERR_MAX_PLAYERS));
		if (!check_filename(av[*n_arg]))
			return (0);
		vm->player[vm->n_players].file_name = ft_strdup(av[(*n_arg)++]);
		vm->player[vm->n_players].id = num;
		vm->player[vm->n_players].i = vm->n_players;
		vm->n_players += 1;
		return (1);
	}
}

static int	flag_dump(t_vm *vm, int ac, char **av, int *n_arg)
{
	int		num;

	if (*n_arg + 2 >= ac || vm->dump != 0)
		return (error_vm(ERR_FLAG));
	else
	{
		(*n_arg)++;
		if (!check_atoi(av[*n_arg]))
			return (error_vm(ERR_FLAG));
		num = ft_atoi(av[(*n_arg)++]);
		if (num < 1)
			return (error_vm(ERR_FLAG));
		vm->dump = num;
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
			vm->player[i].id = 0;
		if (vm->player[i].id != 0 && vm->player[i].i >= 0)
		{
			if (vm->player[vm->player[i].id - 1].id == vm->player[i].id &&
				vm->player[vm->player[i].id - 1].i != vm->player[i].i)
				return (0);
			tmp = vm->player[vm->player[i].id - 1];
			vm->player[vm->player[i].id - 1] = vm->player[i];
			vm->player[i] = tmp;
			vm->player[i].i = -1;
			i = -1;
		}
	}
	i = -1;
	while (++i < vm->n_players)
		if (vm->player[i].id == 0)
			vm->player[i].id = i + 1;
	return (vm->n_players == 0 ? 0 : 1);
}

static int	parse_flags(t_vm *vm, int ac, char **av, int *n_arg)
{
	if ((!ft_strcmp(av[*n_arg], "-v") && vm->v) ||
		(!ft_strcmp(av[*n_arg], "-d") && vm->d))
		return (error_vm(ERR_FLAG));
	else if (!ft_strcmp(av[*n_arg], "-dump"))
		return (flag_dump(vm, ac, av, n_arg));
	else if (!ft_strcmp(av[*n_arg], "-n"))
		return (flag_n(vm, ac, av, n_arg));
	else if (!ft_strcmp(av[*n_arg], "-v"))
	{
		vm->v = 1;
		if (*n_arg + 1 < ac && check_atoi(av[*n_arg + 1]))
			vm->v_cycle = ft_atoi(av[++(*n_arg)]);
	}
	else if (!ft_strcmp(av[*n_arg], "-d"))
	{
		vm->d = 2;
		if (*n_arg + 1 < ac && check_atoi(av[*n_arg + 1]))
			vm->d = (!ft_strcmp(av[++(*n_arg)], "1") ? 1 : 2);
	}
	else
		return (error_vm(ERR_FLAG));
	(*n_arg)++;
	return (1);
}

int			parse_args(t_vm *vm, int ac, char **av)
{
	int		n_arg;

	n_arg = 1;
	if (ac < 2)
		return (error_vm(ERR_FLAG));
	while (n_arg < ac)
	{
		if (av[n_arg][0] == '-')
		{
			if (!parse_flags(vm, ac, av, &n_arg))
				return (0);
		}
		else
		{
			if (!check_filename(av[n_arg]))
				return (0);
			if (vm->n_players >= MAX_PLAYERS)
				return (error_vm(ERR_MAX_PLAYERS));
			vm->player[vm->n_players].file_name = ft_strdup(av[n_arg++]);
			vm->player[vm->n_players].i = vm->n_players;
			vm->n_players += 1;
		}
	}
	return (!sort_players(vm) ? error_vm(ERR_FLAG) : 1);
}
