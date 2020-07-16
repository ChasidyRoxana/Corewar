/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:59:56 by tpepperm          #+#    #+#             */
/*   Updated: 2020/07/16 21:41:33 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

static void	write_name_comment(int fd, t_disasm *disasm)
{
	write(fd, ".name \"", 7);
	write(fd, disasm->name, ft_strlen(disasm->name));
	write(fd, "\"\n.comment \"", 12);
	write(fd, disasm->comment, ft_strlen(disasm->comment));
	write(fd, "\"\n\n", 3);
}

static void	write_commands(int fd, t_disasm *disasm)
{
	char		*num;
	t_command	*tmp;
	t_arg		*tmp_arg;

	tmp = disasm->ops;
	while (tmp)
	{
		tmp_arg = tmp->args;
		write(fd, OP(tmp->op_code).name, ft_strlen(OP(tmp->op_code).name));
		write(fd, " ", 1);
		while (tmp_arg)
		{
			if (tmp_arg != tmp->args)
				write(fd, ", ", 2);
			num = ft_itoa(tmp_arg->arg);
			if (tmp_arg->type != T_IND)
				write(fd, (tmp_arg->type == T_REG ? "r" : "%"), 1);
			write(fd, num, ft_strlen(num));
			free(num);
			tmp_arg = tmp_arg->next;
		}
		write(fd, "\n", 1);
		tmp = tmp->next;
	}
}

int			write_to_file(t_disasm *disasm)
{
	int fd;

	if ((fd = open(disasm->filename, O_CREAT | O_TRUNC | O_RDWR, 755)) == -1)
		return (error_disasm(ERR_CRT_FILE));
	write_name_comment(fd, disasm);
	write_commands(fd, disasm);
	return (1);
}
