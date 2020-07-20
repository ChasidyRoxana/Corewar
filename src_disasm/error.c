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
		ft_fdprintf(2, "Usage: ./disasm [filename.cor]\n");
	else if (error == ERR_FILE_NAME)
		ft_fdprintf(2, "Use [filename].cor\n");
	else if (error == ERR_OPEN_FILE)
		ft_fdprintf(2, "Could not open file\n");
	else if (error == ERR_HEADER)
		ft_fdprintf(2, "Something is wrong with the header\n");
	else if (error == ERR_COMMAND)
		ft_fdprintf(2, "Something is wrong with the commands\n");
	else if (error == ERR_CRT_FILE)
		ft_fdprintf(2, "Could not CREATE/OPEN file\n");
	return (0);
}
