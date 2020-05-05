/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 20:05:22 by marvin            #+#    #+#             */
/*   Updated: 2020/05/05 20:05:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/* принимает номер ошибки (предлагаю ошибки задефайнить, чтобы отправлять не 
** непонятные цифры); лист, из которго берёт строку и её номер; число, которое
** вернёт функция
*/
int			error_line(int error, t_gnl *gnl, int return_num)
{
	write(2, "Error\n", 7);
	if (error == ERR_OPEN_FILE)
		write(2, "Сould not open file\n", 22);// Помогите гугл-переводчику сделать его работу
	else if (error == ERR_MALLOC)
		write(2, "Malloc ne v sebe\n", 18);
	else if (error == ERR_DOT)
		write(2, "slishkom mnogo .command\n", 25);
	else if (error == ERR_FILE_NAME)
		write(2, "Nujen [filename].s\n", 20);
	//	printf("[%d]:%s\n", gnl->nb_line, gnl->line);
	return (return_num);
}

// проверка на переполнение
// return (1) - есть length_error, то есть места больше нет
// return (0) - все ок
int		length_error(int index, int length)
{
	// все-таки сколько записываем? (128 + 1) или (128) для имени, 
    // (2048) или (2048 + 1) для коммента (?)
    if (index >= length)
	{
		if (length == PROG_NAME_LENGTH)
			write(2, "The name of the champeon is too long\n", 38);
		else if (length == COMMENT_LENGTH)
			write(2, "The comment is too long\n", 25);
		return (1);
	}
	return(0);
}

int     error_name_comment(char *message, int nb_line)
{
    if (ft_strcmp(message, NAME_CMD_STRING) == 0)
    {
        write(2, "Error in name of the champeon in line: ", 40);
        ft_printf("%d\n", nb_line);
    }
    else if (ft_strcmp(message, COMMENT_CMD_STRING) == 0)
    {
        write(2, "Error in comment in line: ", 27);
        ft_printf("%d\n", nb_line);
    }
    return (0);
}
