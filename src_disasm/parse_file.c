/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:32:59 by marvin            #+#    #+#             */
/*   Updated: 2020/07/08 15:46:47 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

static int			read_n_byte(int fd, char str[], int n_byte)
{
	int				byte_read;

	byte_read = read(fd, str, n_byte);
	if (byte_read != n_byte)
		return (0);
	str[byte_read] = '\0';
	return (1);
}

static int	get_uint(int fd, int n_byte)
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

static int			parse_header(t_disasm *disasm, int fd)
{
	if (get_uint(fd, 4) != COREWAR_EXEC_MAGIC)
		return (0);
	if (!read_n_byte(fd, disasm->name, PROG_NAME_LENGTH))
		return (0);
	get_uint(fd, 4);
	if ((disasm->prog_length = get_uint(fd, 4)) < 0 ||
		disasm->prog_length > CHAMP_MAX_SIZE)
		return (0);
	if (!read_n_byte(fd, disasm->comment, COMMENT_LENGTH))
		return (0);
	get_uint(fd, 4);
	return (1);
}

int					parse_file(t_disasm *disasm, char *file)
{
	int		fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (0);
	if (parse_header(disasm, fd) &&
		parse_commands(disasm, fd))
		return (1);
	close(fd);
	return (0);
}
