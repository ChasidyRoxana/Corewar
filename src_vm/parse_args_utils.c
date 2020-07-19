/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 20:53:21 by croxana           #+#    #+#             */
/*   Updated: 2020/07/16 20:53:21 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		check_filename(char *name)
{
	int		length;

	length = ft_strlen(name);
	if (length < 5)
		return (error_vm(ERR_FILE_NAME));
	if (ft_strcmp(&name[length - 4], ".cor") == 0)
		return (1);
	else
		return (error_vm(ERR_FILE_NAME));
}

int		check_atoi(char *av)
{
	int			i;
	long long	num;
	int			flag;

	i = 0;
	num = 0;
	flag = 1;
	while ((av[i] >= 9 && av[i] <= 13) || av[i] == 32)
		i++;
	if (av[i] == '-')
		flag = -1;
	if (av[i] == '+' || av[i] == '-')
		i++;
	if (av[i] > '9' || av[i] < '0')
		return (0);
	while (av[i] && av[i] >= 48 && av[i] <= 57 && num < (long long)2147483648)
		num = num * 10 + (av[i++] - '0');
	if (av[i] != '\0' || (num > (long long)2147483647 && flag == 1) ||
		(num > (long long)2147483648 && flag == -1))
		return (0);
	return (1);
}
