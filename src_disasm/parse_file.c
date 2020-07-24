/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:59:49 by tpepperm          #+#    #+#             */
/*   Updated: 2020/07/24 17:57:48 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

static int	read_n_byte(int fd, char str[], int n_byte)
{
	int				byte_read;

	byte_read = read(fd, str, n_byte);
	if (byte_read != n_byte)
		return (0);
	str[byte_read] = '\0';
	return (1);
}

static int	get_int(int fd, int n_byte)
{
	unsigned char	str[n_byte + 1];
	int				result;
	int				i;

	result = 0;
	i = -1;
	if (n_byte > 4 || !read_n_byte(fd, (char*)str, n_byte))
		return (0);
	while (++i < n_byte)
		result |= (unsigned int)str[i] << ((n_byte - i - 1) * 8);
	return (result);
}

static int	parse_header(t_disasm *disasm, int fd)
{
	if (get_int(fd, 4) != COREWAR_EXEC_MAGIC)
		return (error_disasm(ERR_HEADER));
	if (!read_n_byte(fd, disasm->name, PROG_NAME_LENGTH))
		return (error_disasm(ERR_HEADER));
	get_int(fd, 4);
	if ((disasm->prog_length = get_int(fd, 4)) < 0 ||
		disasm->prog_length > CHAMP_MAX_SIZE)
		return (error_disasm(ERR_CHAMP_SIZE));
	if (!read_n_byte(fd, disasm->comment, COMMENT_LENGTH))
		return (error_disasm(ERR_HEADER));
	get_int(fd, 4);
	return (1);
}

int			parse_file(t_disasm *disasm, char *file)
{
	int		fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (error_disasm(ERR_OPEN_FILE));
	if (parse_header(disasm, fd) &&
		parse_commands(disasm, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
