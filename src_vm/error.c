/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 21:45:43 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/24 19:16:41 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		error_line(int error, char *str)
{
	if (error == ERR_OPEN_FILE)
		ft_fdprintf(2, "Can't read source file %s\n", str);
	return (0);
}

int		error_vm(int error)
{
	if (error == ERR_FILE_NAME)
		ft_fdprintf(2, "The champion file should be named [filename].cor\n");
	else if (error == ERR_MAX_PLAYERS)
		ft_fdprintf(2, "Too many champions\n");
	else if (error == ERR_FLAG)
		ft_fdprintf(2, "Error with flags\nUsage: ./corewar [-v -d "
		"-dump N] [[-n N] [filename].cor] ...\n"
		"-v / -v N: visual / visual after N cycles\n"
		"-d / -d 1: debug / show final number of cycles\n"
		"-n N: number of player(1 <= N <= 4)\n"
		"-dump N: at the end of N cycles, dump the memory and quit the game\n");
	else if (error == ERR_MAGIC_HEADER)
		ft_fdprintf(2, "Wrong magic header\n");
	else if (error == ERR_NAME)
		ft_fdprintf(2, "Error with champion name\n");
	else if (error == ERR_COMMENT)
		ft_fdprintf(2, "Error with champion comment\n");
	else if (error == ERR_CHAMP_SIZE)
		ft_fdprintf(2, "Wrong champion size\n");
	else if (error == ERR_MALLOC)
		ft_fdprintf(2, "Error with memory allocation\n");
	return (0);
}

int		error_champ_size(t_player *player)
{
	if (player->champ_size < 1)
		ft_fdprintf(2, "The champion size is too small\n");
	else if (player->champ_size > CHAMP_MAX_SIZE)
		ft_fdprintf(2, "The champion \"%s\" size is too big. %d > %d "
		"CHAMP_MAX_SIZE\n", player->name, player->champ_size, CHAMP_MAX_SIZE);
	return (0);
}
