/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 20:05:22 by marvin            #+#    #+#             */
/*   Updated: 2020/07/22 23:01:24 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			error_common(int error)
{
	ft_fdprintf(2, "Error: ");
	if (error == ERR_OPEN_FILE)
		ft_fdprintf(2, "Сould not open file\n");
	else if (error == ERR_MALLOC)
		ft_fdprintf(2, "Malloc didn't work\n");
	else if (error == ERR_FILE)
		ft_fdprintf(2, "Empty file\n");
	else if (error == ERR_FILE_NAME)
		ft_fdprintf(2, "Use [filename].s\n");
	else if (error == ERR_NAME_LENGTH)
		ft_fdprintf(2, "The name of the champeon is too long\n");
	else if (error == ERR_COMMENT_LENGTH)
		ft_fdprintf(2, "The comment is too long\n");
	else if (error == ERR_NO_NAME_COMMENT)
		ft_fdprintf(2, "There is no name or comment\n");
	else if (error == ERR_NOT_COMMAND)
		ft_fdprintf(2, "There is no such command. Use [.name] or [.comment]\n");
	else if (error == ERR_NO_END)
		ft_fdprintf(2, "Unexpected end of input. No new line at the end\n");
	else if (error == ERR_NO_OP)
		ft_fdprintf(2, "No commands in .s file\n");
	else if (error == ERR_CREATE_FILE)
		ft_fdprintf(2, "Couldn't create file for writing\n");
	return (0);
}

int			length_error(int index, int length)
{
	if (index >= length)
	{
		if (length == PROG_NAME_LENGTH)
			return (error_common(ERR_NAME_LENGTH));
		else if (length == COMMENT_LENGTH)
			return (error_common(ERR_COMMENT_LENGTH));
	}
	return (1);
}

int			error_args(int error, t_command *comm, char *str, int n_sym)
{
	if (error == ERR_ARG)
		ft_fdprintf(2, "Invalid type of parameter %d for instruction '%s' ",
			comm->num_args + 1, OP(comm->op - 1).name);
	else if (error == ERR_MAX_ARG)
		ft_fdprintf(2, "Too many arguments for instruction '%s' ",
		OP(comm->op - 1).name);
	else if (error == ERR_MIN_ARG)
		ft_fdprintf(2, "Not enough arguments for instruction '%s' ",
		OP(comm->op - 1).name);
	else if (error == ERR_NO_ARGS)
		ft_fdprintf(2, "No arguments for instruction '%s' ",
		OP(comm->op - 1).name);
	else if (error == ERR_LABEL)
		ft_fdprintf(2, "No such label '%s' ", str);
	error_line(ERR_ARG, comm->gnl_line, n_sym);
	return (0);
}

int			error_line(int error, t_gnl *gnl, int n_sym)
{
	if (error == ERR_NAME)
		ft_fdprintf(2, "Error in name of the champeon in line: ", 40);
	else if (error == ERR_COMMENT)
		ft_fdprintf(2, "Error in comment in line: ", 27);
	else if (error == ERR_SYNTAX)
		ft_fdprintf(2, "Syntax error ", 14);
	else if (error == ERR_REG)
		ft_fdprintf(2, "Reg number is out of bounds ", 29);
	else if (error == ERR_LEXICAL)
		ft_fdprintf(2, "Lexical error ", 15);
	else if (error == ERR_OP)
		ft_fdprintf(2, "Invalid instruction ", 21);
	if (gnl)
	{
		ft_fdprintf(2, "on line [%d]", gnl->nb_line);
		if (n_sym >= 0)
			ft_fdprintf(2, " at symbol [%d]", (n_sym + 1));
		ft_fdprintf(2, ":\n%s\n", gnl->line);
	}
	return (0);
}
