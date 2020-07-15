/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:59:41 by tpepperm          #+#    #+#             */
/*   Updated: 2020/07/15 22:06:50 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

static int	get_int(unsigned char code[], int *i, int byte)
{
	int		result;
	int		j;

	result = 0;
	j = -1;
	while (++j < byte)
		result |= (unsigned int)code[(*i)++] << ((byte - j - 1) * 8);
	if ((result >> (byte * 8 - 1)) & 1)
	{
		j = byte * 8;
		while (j < 32)
			result |= 1 << j++;
	}
	return (result);
}

static int	get_arg(unsigned char code[], int *i, int t_dir_size, t_arg *tmp)
{
	if (tmp->type == T_REG)
		return (get_int(code, i, 1));
	else if (tmp->type == T_IND)
		return (get_int(code, i, 2));
	else
		return (get_int(code, i, (t_dir_size ? 2 : 4)));
}

static int	fill_args(t_command *comm, unsigned char code[], int *i)
{
	t_arg	*tmp;
	int		arg_code;
	int		j;

	j = 6;
	arg_code = get_int(code, i, 1);
	while (j > 0 && ((arg_code >> j) & 3) != 0)
	{
		if (!new_arg(comm))
			return (0);
		tmp = comm->args;
		while (tmp->next)
			tmp = tmp->next;
		tmp->type = (arg_code >> j) & 3;
		if (tmp->type == IND_CODE)
			tmp->type = T_IND;
		if ((OP(comm->op_code).args[3 - j / 2] & tmp->type) == 0)
			return (0);
		tmp->arg = get_arg(code, i, OP(comm->op_code).t_dir_size, tmp);
		j -= 2;
	}
	return ((3 - j / 2 == OP(comm->op_code).nb_arg) ? 1 : 0);
}

static int	fill_command(t_command *comm, unsigned char code[], int *i)
{
	if (OP(comm->op_code).type_arg_code)
	{
		if (!fill_args(comm, code, i))
			return (0);
	}
	else
	{
		if (!new_arg(comm))
			return (0);
		comm->args->type = OP(comm->op_code).args[0];
		comm->args->arg = get_int(code, i,
			(OP(comm->op_code).t_dir_size ? 2 : 4));
	}
	return (1);
}

int			parse_commands(t_disasm *disasm, int fd)
{
	unsigned char	code[disasm->prog_length + 1];
	int				n;
	int				i;

	n = read(fd, code, disasm->prog_length + 1);
	if (n != disasm->prog_length)
		return (error_disasm(ERR_COMMAND));
	i = 0;
	while (i < n)
	{
		if (!new_command(disasm))
			return (error_disasm(ERR_COMMAND));
		disasm->ops_last->op_code = get_int(code, &i, 1) - 1;
		if (disasm->ops_last->op_code < 0 || disasm->ops_last->op_code > 15)
			return (error_disasm(ERR_COMMAND));
		if (!fill_command(disasm->ops_last, code, &i))
			return (error_disasm(ERR_COMMAND));
	}
	return (1);
}
