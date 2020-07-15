/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 21:56:04 by tpepperm          #+#    #+#             */
/*   Updated: 2020/07/15 22:06:43 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

int		error_disasm(int error)
{
	if (error == ERR_USAGE)
		write(2, "Usage: ./disasm [file.cor]\n", 28);
	else if (error == ERR_FILE_NAME)
		write(2, "Use [filename].cor\n", 20);
	else if (error == ERR_OPEN_FILE)
		write(2, "Could not open file\n", 21);
	else if (error == ERR_HEADER)
		write(2, "Something is wrong with the header\n", 36);
	else if (error == ERR_COMMAND)
		write(2, "Something is wrong with the commands\n", 38);
	else if (error == ERR_CRT_FILE)
		write(2, "Could not CREATE/OPEN file\n", 28);
	return (0);
}
