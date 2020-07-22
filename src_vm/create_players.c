/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:03:40 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/22 21:03:35 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		check_four_bytes(t_player *player)
{
	int				z;
	int				result;
	unsigned char	buf[5];

	z = -1;
	result = 0;
	read(player->fd, buf, 4);
	buf[4] = '\0';
	while (++z < 4)
		result |= (unsigned int)buf[z] << ((3 - z) * 8);
	return (result);
}

int		check_player(t_player *player)
{
	unsigned char buf[4];

	if (check_four_bytes(player) != COREWAR_EXEC_MAGIC)
		return (error_vm(ERR_MAGIC_HEADER));
	if (!read(player->fd, player->name, PROG_NAME_LENGTH))
		return (error_vm(ERR_NAME));
	read(player->fd, buf, 4);
	if ((player->champ_size = check_four_bytes(player)) < 1 ||
		player->champ_size > CHAMP_MAX_SIZE)
		return (error_champ_size(player));
	if (!read(player->fd, player->comment, COMMENT_LENGTH))
		return (error_vm(ERR_COMMENT));
	read(player->fd, buf, 4);
	return (1);
}

int		fill_arena(t_vm *vm, t_player player, int color)
{
	int				j;
	int				i;
	int				read_bytes;
	unsigned char	code[player.champ_size + 1];

	read_bytes = read(player.fd, code, player.champ_size + 1);
	if (read_bytes != player.champ_size)
		return (error_vm(ERR_CHAMP_SIZE));
	code[player.champ_size] = '\0';
	j = -1;
	i = player.i;
	while (++j < player.champ_size)
	{
		vm->arena[i].i = code[j];
		vm->arena[i].color = (j == 0) ? (color + 1) : color;
		vm->arena[i].prev_color = color;
		i++;
	}
	return (1);
}

int		create_player(t_vm *vm)
{
	int	i;
	int j;
	int color;
	int champ_place;

	j = 0;
	i = 0;
	color = 1;
	champ_place = MEM_SIZE / vm->n_players;
	while (j < vm->n_players)
	{
		if ((vm->player[j].fd = open(vm->player[j].file_name, O_RDONLY)) < 0)
			return (error_line(ERR_OPEN_FILE, vm->player[j].file_name));
		vm->player[j].i = i;
		if (!check_player(&vm->player[j]))
			return (0);
		if (!fill_arena(vm, vm->player[j], color))
			return (0);
		close(vm->player[j].fd);
		i += champ_place;
		color += 2;
		j++;
	}
	return (1);
}
