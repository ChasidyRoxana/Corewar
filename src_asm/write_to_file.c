/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 17:40:49 by marvin            #+#    #+#             */
/*   Updated: 2020/07/21 23:45:27 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
** Зписывает число в массив. Деление на 256 - диапазон значений одного
** байта - 0...255
*/

void		write_int(int fd, unsigned int num, int byte)
{
	unsigned char	res[byte + 1];
	int				i;

	i = byte;
	res[i--] = '\0';
	while (i >= 0)
	{
		res[i] = (num % 256);
		num /= 256;
		i--;
	}
	write(fd, res, byte);
}

/*
** Записывает код операции, код аргументов (если есть),
** код каждого аргумента (размер зависит от типа аргумента).
*/

static void	write_commands(t_asm *asmb, int fd)
{
	t_command	*comm;
	t_args		*tmp;

	comm = asmb->comm;
	while (comm)
	{
		if (comm->op < 1)
			return ;
		write_int(fd, comm->op, 1);
		if (OP(comm->op - 1).type_arg_code)
			write_int(fd, comm->args_type, 1);
		tmp = comm->args;
		while (tmp)
		{
			if (tmp->type == T_REG)
				write_int(fd, tmp->arg, 1);
			else if (tmp->type == T_IND ||
				(tmp->type == T_DIR && OP(comm->op - 1).t_dir_size))
				write_int(fd, tmp->arg, 2);
			else
				write_int(fd, tmp->arg, 4);
			tmp = tmp->next;
		}
		comm = comm->next;
	}
}

/*
** Создание файла. Запись полей header'а.
** После строк должны быть 4 нулевых байта.
** Запись команд.
*/

int			write_to_file(t_asm *asmb)
{
	int		fd;

	if ((fd = open(asmb->filename, O_CREAT | O_TRUNC | O_RDWR, 755)) == -1)
		return (error_common(ERR_CREATE_FILE));
	write_int(fd, asmb->header.magic, 4);
	write(fd, asmb->header.prog_name, PROG_NAME_LENGTH);
	write_int(fd, 0, 4);
	write_int(fd, asmb->header.prog_size, 4);
	write(fd, asmb->header.comment, COMMENT_LENGTH);
	write_int(fd, 0, 4);
	write_commands(asmb, fd);
	close(fd);
	return (1);
}
