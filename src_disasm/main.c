/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 23:19:46 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/02 14:15:09 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

int			check_filename(char *name)
{
	int			length;
	t_disasm	disasm;

	ft_memset(&disasm, 0, sizeof(disasm));
	length = ft_strlen(name);
	// проверяем, что у нас файл "*.cor" (то есть хотя бы  
	// один символ и расширение .cor)
	if (length < 5)
		return (error_disasm(ERR_FILE_NAME));
	if (ft_strcmp(&name[length - 4], ".cor") == 0)
	{
		disasm.filename = ft_strnew(length - 2);
		ft_strncpy(disasm.filename, name, (length - 4));
		ft_strcat(disasm.filename, ".s");
	}
	else
		return (error_disasm(ERR_FILE_NAME));
	// printf("FILENAME: %s\n", disasm.filename);
	return (1);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Usage: ./disasm [file.cor]\n", 28);
		return (1);
	}
	// проверяем .cor
	if (!check_filename(argv[1]))
		return (1);

	// парсим файл и записываем все в структуру
	// parse_file();
	
	// записываем данные из структуры в файл
	// write_to_file();
	return (0);
}