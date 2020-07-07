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

// нужна ли проверка на то, что после -dump идёт
// именно число, без всяких букв и лишних знаков?
static int	flag_dump(t_vm *vm, int ac, char **av, int *n_arg)
{
	// int		i;


	if (n_arg + 2 >= ac || vm->dump != 0)
		return (0);
	else
	{
		// i = 0;
		*n_arg++;
		// while (av[*n_arg][i] >= '0' && av[*n_arg][i] <= '9')
		// 	i++;
		// if (av[*n_arg][i] == '\0')
			vm->dump = ft_atoi(av[*n_arg++]);
		// else
		// {
		// 	write(2, "Usage: ...", 11);
		// 	return (0);
		// }
		return (1);
	}
}

int			parse_args(t_vm *vm, int ac, char **av)
{
	int		n_arg;

	n_arg = 1;
	if (ac < 2)
	{
		write(2, "Usage: ...", 11);
		return (0);
	}
	while (n_arg < ac)
	{
		if (!ft_strcmp(av[n_arg], "-dump"))
		{
			if (!flag_dump(vm, ac, av, &n_arg))
			{
				write(2, "Usage: ...", 11);
				return (0);
			}
		}
		if (!ft_strcmp(av[n_arg], "-n"))
		{
			;
		}
		n_arg++;
	}
	return (1);
}
