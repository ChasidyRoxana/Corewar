/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:34:35 by marvin            #+#    #+#             */
/*   Updated: 2020/07/02 17:34:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

static int		new_command(t_disasm *disasm)
{
	if (!disasm->ops)
	{
		if (!(disasm->ops = (t_command*)malloc(sizeof(t_command))))
			return (0);
		disasm->ops_last = disasm->ops;
	}
	else
	{
		if (!(disasm->ops_last->next = (t_command*)malloc(sizeof(t_command))))
			return (0);
		disasm->ops_last = disasm->ops_last->next;
	}
	ft_memset((void*)disasm->ops_last, 0, sizeof(t_command));
	return (1);
}

static int		get_int(char code[], int *i, int byte)
{
	int		result;
	int		j;

	result = 0;
	j = -1;
	while (++j < byte)
		result |= (int)code[(*i)++] << ((byte - j - 1) * 8);
	return (result);
}

int				parse_commands(t_disasm *disasm, int fd)
{
	unsigned char	code[disasm->prog_length + 2];
	int				n;
	int				i;
	int				arg_code;

	n = read(fd, code, disasm->prog_length + 1);
	if (n != disasm->prog_length){printf("Error prog_length\n");
		return (0);}
	i = 0;
	while (i < n)
	{
		if (!new_command(disasm))
			return (0);
		disasm->ops_last->op_code = get_int(code, &i, 1);
		if (disasm->ops_last->op_code < 1 || disasm->ops_last->op_code > 16)
			return (0);
		if (OP(disasm->ops_last->op_code).type_arg_code)
			arg_code = get_int(code, &i, 1);
		// првоеряя код аргументов заполнять аргументы
	}
	return (1);
}
