/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 20:05:22 by marvin            #+#    #+#             */
/*   Updated: 2020/05/06 20:43:12 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int	error_without_gnl(int error, int return_num)
{
	write(2, "Error: ", 8);
	if (error == ERR_OPEN_FILE)
		write(2, "Сould not open file\n", 22);// Помогите гугл-переводчику сделать его работу
	else if (error == ERR_MALLOC)
		write(2, "Malloc ne v sebe\n", 18);
	else if (error == ERR_DOT)
		write(2, "Slishkom mnogo .command\n", 25);
	else if (error == ERR_FILE_NAME)
		write(2, "Nujen [filename].s\n", 20);
	else if (error == ERR_NO_NAME_COMMENT)
		write(2, "There is no name or comment\n", 29);
	else if (error == ERR_NOT_COMMAND)
		write(2, "There is no such command. Use [.name] or [.comment]\n", 53);
	else if (error == ERR_NAME_LENGTH)
		write(2, "The name of the champeon is too long\n", 38);
	else if (error == ERR_COMMENT_LENGTH)
		write(2, "The comment is too long\n", 25);
	return (return_num);
}

/* принимает номер ошибки (предлагаю ошибки задефайнить, чтобы отправлять не 
** непонятные цифры); лист, из которго берёт строку и её номер; число, которое
** вернёт функция
*/
int			error_line(int error, t_gnl *gnl, int return_num)
{
	if (!gnl)
		return (error_without_gnl(error, return_num));
	else if (error == ERR_NAME)
		write(2, "Error in name of the champeon in line: ", 40);
	else if (error == ERR_COMMENT)
		write(2, "Error in comment in line: ", 27);
	// if (gnl)
		// printf("[%d]: %s\n", gnl->nb_line, gnl->line);
	return (return_num);
}

// проверка на переполнение
// return (1) - есть length_error, то есть места больше нет
// return (0) - все ок
int		length_error(int index, int length) // обработать, чтобы выводилось сколько лишнего
{
    if (index >= length)
	{
		if (length == PROG_NAME_LENGTH)
			return (error_line(ERR_NAME_LENGTH, NULL, 1));
		else if (length == COMMENT_LENGTH)
			return (error_line(ERR_COMMENT_LENGTH, NULL, 1));
		return (1);
	}
	return(0);
}

