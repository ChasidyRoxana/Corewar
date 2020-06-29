/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 20:05:22 by marvin            #+#    #+#             */
/*   Updated: 2020/06/29 22:42:41 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int	error_without_gnl(int error, int return_num)
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
	else if (error == ERR_NO_END)
	// В оригинальном асм:
	// Syntax error - unexpected end of input (Perhaps you forgot to end with a newline?)\n
	// Предлагаю покороче сделать
		write(2, "Unexpected end of input. No new line at the end.\n", 50);
	return (return_num);
}

int			error_args(int error, t_gnl *gnl, t_command *comm, int n_sym)
{
	if (comm)
	{
		if (error == ERR_ARG)
			printf("Invalid type of %d parameter for instruction '%s' ", 
				comm->num_args, OP(comm->op - 1).name);
		else if (error == ERR_MAX_ARG)
			printf("Too many arguments for instruction '%s' ", OP(comm->op - 1).name);
		else if (error == ERR_MIN_ARG)
			printf("Not enough arguments for instruction '%s' ", OP(comm->op - 1).name);
		else if (error == ERR_NO_ARGS)
			printf("No arguments for instruction '%s' ", OP(comm->op - 1).name);
	}
	error_line(ERR_ARG, gnl, 0, n_sym);
	return (0);
}

int 		count_tabs(t_gnl *gnl, int n_sym)
{
	int i;

	i = 0;
	while (n_sym >= 0)
	{
		// printf(".%c. %d\n", gnl->line[n_sym], gnl->line[n_sym]);
		if (gnl->line[n_sym] == '\t')
			i += sizeof(gnl->line[n_sym]);
		else
			i += 1;
		n_sym--;
	}
	// printf("i: %d\n", i);
	return (i);
}

/* принимает номер ошибки; лист, из которго берёт строку и её номер;
** число, которое вернёт функция; номер символа в строке
*/
int			error_line(int error, t_gnl *gnl, int return_num, int n_sym)
{
	// n_sym = 0; ////
	if (!gnl)
		return (error_without_gnl(error, return_num));
	else if (error == ERR_NAME)
		write(2, "Error in name of the champeon in line: ", 40);
	else if (error == ERR_COMMENT)
		write(2, "Error in comment in line: ", 27);
	else if (error == ERR_SYNTAX)
		write(2, "Syntax error ", 14);
	else if (error == ERR_REG)
		write(2, "Reg number is out of bounds ", 29);
	else if (error == ERR_LEXICAL)
		write(2, "Lexical error ", 15);
	else if (error == ERR_LABEL)//////
		write(2, "No such label", 15);//////
	else if (error == ERR_OP)
		write(2, "Invalid instruction ", 21);
	if (gnl)
	{
		printf("on line [%d]", gnl->nb_line);
		if (n_sym >= 0)
			printf(" at symbol [%d]:\n", (n_sym + 1));
		printf(":\n%s\n", gnl->line);
		// n_sym = count_tabs(gnl, n_sym);
		// ft_printf("%*c^\n", n_sym, ' ');
	}
	return (return_num);
}

// проверка на переполнение
// return (1) - есть length_error, то есть места больше нет
// return (0) - все ок
int			length_error(int index, int length) // обработать, чтобы выводилось сколько лишнего
{
	if (index >= length)
	{
		if (length == PROG_NAME_LENGTH)
			return (error_line(ERR_NAME_LENGTH, NULL, 1, -1));
		else if (length == COMMENT_LENGTH)
			return (error_line(ERR_COMMENT_LENGTH, NULL, 1, -1));
		return (1);// на какой случай этот ретёрн?
	}
	return (0);
}
