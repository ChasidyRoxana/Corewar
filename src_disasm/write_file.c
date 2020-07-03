/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 19:19:46 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/03 17:49:53 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

static void		write_name_comment(int fd, t_disasm *disasm) 
{
	write(fd, ".name \"", 7);
	write(fd, disasm->name, ft_strlen(disasm->name));
	write(fd, "\"\n.comment \"", 12);
	write(fd, disasm->comment, ft_strlen(disasm->comment));
	write(fd, "\"\n\n", 3);
}

static void		write_commands(int fd, t_disasm *disasm)
{
	int 		flag;
	char		*num;
	t_command 	*tmp;
	t_arg		*tmp_arg;

	tmp = disasm->ops;
	while (tmp)
	{
		flag = 0;
		tmp_arg = tmp->args;
		write(fd, OP(tmp->op_code).name, ft_strlen(OP(tmp->op_code).name));
		write(fd, " ", 1);
		while (tmp_arg)
		{
			if (flag != 0)
				write(fd, ", ", 2);
			num = ft_itoa(tmp_arg->arg); // туплю ???
			if (tmp_arg->type == T_REG)
				write(fd, "r", 1);
			else if (tmp_arg->type == T_DIR)
				write(fd, "%", 1); // почему горит %?
			write(fd, num, ft_strlen(num));
			tmp_arg = tmp_arg->next;
			flag += 1;
		}
		write(fd, "\n", 1);
		tmp = tmp->next;
	}
}

int				write_to_file(t_disasm *disasm)
{
	int fd;

	// printf("NAME: %s\nCOMMENT: %s\n", disasm->name, disasm->comment);
	if ((fd = open(disasm->filename, O_CREAT | O_TRUNC | O_RDWR, 755)) == -1)
		return (error_disasm(ERR_CREATE_FILE));

	// записываем имя и коммент
	write_name_comment(fd, disasm);

	// записываем команды
	write_commands(fd, disasm);

	// добавить в файл в конце \0
	// write(fd, "\0", 1);
	return (1);
}