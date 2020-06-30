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

int			error_common(int error)
{
	write(2, "Error: ", 8);
	if (error == ERR_OPEN_FILE)
		write(2, "Сould not open file\n", 22);
	else if (error == ERR_MALLOC)
		write(2, "Malloc ne v sebe\n", 18);
	// else if (error == ERR_DOT)
	// 	write(2, "Slishkom mnogo .command\n", 25);
	else if (error == ERR_FILE_NAME)
		write(2, "Nujen [filename].s\n", 20);
	else if (error == ERR_NAME_LENGTH)
		write(2, "The name of the champeon is too long\n", 38);
	else if (error == ERR_COMMENT_LENGTH)
		write(2, "The comment is too long\n", 25);
	else if (error == ERR_NO_NAME_COMMENT)
		write(2, "There is no name or comment\n", 29);
	else if (error == ERR_NOT_COMMAND)
		write(2, "There is no such command. Use [.name] or [.comment]\n", 53);
	else if (error == ERR_NO_END)
		write(2, "Unexpected end of input. No new line at the end.\n", 50);
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

// проверка на переполнение
// return (0) - есть length_error, то есть места больше нет
// return (1) - все ок
int			length_error(int index, int length) // обработать, чтобы выводилось сколько лишнего
{
	if (index >= length)
	{
		if (length == PROG_NAME_LENGTH)
			return (error_common(ERR_NAME_LENGTH));
		else if (length == COMMENT_LENGTH)
			return (error_common(ERR_COMMENT_LENGTH));
		return (0);// на какой случай этот ретёрн?
	}
	return (1);
}

int			error_args(int error, t_command *comm, char *str, int n_sym)
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
	else if (error == ERR_LABEL)
		printf("No such label '%s' ", str);
	error_line(ERR_ARG, comm->gnl_line, n_sym);
	return (0);
}

/* принимает номер ошибки; лист, из которго берёт строку и её номер;
** число, которое вернёт функция; номер символа в строке
*/
int			error_line(int error, t_gnl *gnl, int n_sym)
{
	// n_sym = 0; ////
	if (error == ERR_NAME)
		write(2, "Error in name of the champeon in line: ", 40);
	else if (error == ERR_COMMENT)
		write(2, "Error in comment in line: ", 27);
	else if (error == ERR_SYNTAX)
		write(2, "Syntax error ", 14);
	else if (error == ERR_REG)
		write(2, "Reg number is out of bounds ", 29);
	else if (error == ERR_LEXICAL)
		write(2, "Lexical error ", 15);
	else if (error == ERR_OP)
		write(2, "Invalid instruction ", 21);
	if (gnl)
	{
		printf("on line [%d]", gnl->nb_line);
		if (n_sym >= 0)
			printf(" at symbol [%d]", (n_sym + 1));
		printf(":\n%s\n", gnl->line);
		// n_sym = count_tabs(gnl, n_sym);
		// ft_printf("%*c^\n", n_sym, ' ');
	}
	return (0);
}
