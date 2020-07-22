/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:59:56 by tpepperm          #+#    #+#             */
/*   Updated: 2020/07/22 22:01:27 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

static void	write_commands(int fd, t_disasm *disasm)
{
	char		*num;
	t_command	*tmp;
	t_arg		*tmp_arg;

	tmp = disasm->ops;
	while (tmp)
	{
		tmp_arg = tmp->args;
		ft_fdprintf(fd, "%s ", OP(tmp->op_code).name);
		while (tmp_arg)
		{
			if (tmp_arg != tmp->args)
				ft_fdprintf(fd, ", ");
			num = ft_itoa(tmp_arg->arg);
			if (tmp_arg->type != T_IND)
				ft_fdprintf(fd, "%c", (tmp_arg->type == T_REG ? 'r' : '%'));
			ft_fdprintf(fd, "%s", num);
			free(num);
			tmp_arg = tmp_arg->next;
		}
		ft_fdprintf(fd, "\n");
		tmp = tmp->next;
	}
}

int			write_to_file(t_disasm *disasm)
{
	int fd;

	if ((fd = open(disasm->filename, O_CREAT | O_TRUNC | O_RDWR, 755)) == -1)
		return (error_disasm(ERR_CRT_FILE));
	ft_fdprintf(fd, ".name \"%s\"\n", disasm->name);
	ft_fdprintf(fd, ".comment \"%s\"\n\n", disasm->comment);
	write_commands(fd, disasm);
	return (1);
}
