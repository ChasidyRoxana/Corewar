/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:34:35 by marvin            #+#    #+#             */
/*   Updated: 2020/07/02 20:57:08 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

static int		get_int(unsigned char code[], int *i, int byte)
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

static int		fill_command(t_command *comm, unsigned char code[], int *i)
{
	t_arg	*tmp;
	int		arg_code;
	int		j;

	j = 6;
	if (OP(comm->op_code).type_arg_code)
	{
		arg_code = get_int(code, i, 1);
		// printf("  arg_code: %d\n", arg_code);
		while (j > 0 && ((arg_code >> j) & 3) != 0)
		{
			if (!new_arg(comm))
				return (0);
			tmp = comm->args;
			while (tmp->next)
				tmp = tmp->next;
			//определяем тип аргумента: 01 рег, 10 дир, 11 инд
			tmp->type = (arg_code >> j) & 3;
			if (tmp->type == IND_CODE)
				tmp->type = T_IND;
			// printf("  type: %d\n", tmp->type);
			//подходит ли тип аргумента
			if ((OP(comm->op_code).args[3 - j / 2] & tmp->type) == 0)
				return (0);
			// printf("  correct type arg\n");
			//читаем нужное количество байт
			if (tmp->type == T_REG || tmp->type == T_IND)
				tmp->arg = get_int(code, i, tmp->type);
			else
				tmp->arg = get_int(code, i,
					(OP(comm->op_code).t_dir_size ? 2 : 4));
			// printf("  arg: %d\n", tmp->arg);
			j -= 2;
		}
	}
	else
	{
		// printf("  no arg_code\n");
		if (!new_arg(comm))
			return (0);
		comm->args->type = OP(comm->op_code).args[0];
		// printf("  type: %d\n", comm->args->type);
		comm->args->arg = get_int(code, i,
			(OP(comm->op_code).t_dir_size ? 2 : 4));
		// printf("  arg: %d\n", comm->args->arg);
	}
	return (1);
}

int				parse_commands(t_disasm *disasm, int fd)
{
	unsigned char	code[disasm->prog_length + 2];
	int				n;
	int				i;

	n = read(fd, code, disasm->prog_length + 1);
	if (n != disasm->prog_length){printf("Error prog_length\n");
		return (0);}
	i = 0;
	while (i < n)
	{
		if (!new_command(disasm))
			return (0);
		disasm->ops_last->op_code = get_int(code, &i, 1) - 1;
		// printf("  op_code: %d\n", disasm->ops_last->op_code);
		if (disasm->ops_last->op_code < 0 || disasm->ops_last->op_code > 15)
			return (0);
		if (!fill_command(disasm->ops_last, code, &i))
			return (0);
	}
	return (1);
}
