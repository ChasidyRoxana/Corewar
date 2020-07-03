/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 23:19:46 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/02 20:56:47 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

int			check_filename(t_disasm *disasm, char *name)
{
	int			length;

	length = ft_strlen(name);
	// проверяем, что у нас файл "*.cor" (то есть хотя бы  
	// один символ и расширение .cor)
	if (length < 5)
		return (error_disasm(ERR_FILE_NAME));
	if (ft_strcmp(&name[length - 4], ".cor") == 0)
	{
		disasm->filename = ft_strnew(length - 2);
		ft_strncpy(disasm->filename, name, (length - 4));
		ft_strcat(disasm->filename, ".s_t");////
	}
	else
		return (error_disasm(ERR_FILE_NAME));
	// printf("FILENAME: %s\n", disasm->filename);
	return (1);
}

int		start_disasm(t_disasm *disasm, char *filename)
{
	// проверяем .cor
	if (!check_filename(disasm, filename))
		return (0);
		
	// парсим файл и записываем все в структуру
	if (!parse_file(disasm, filename))
		return (0);
		
	// записываем данные из структуры в файл
	// !!! Хотя для визуалки это не надо будет, мб и в main все оставить лучше
	if (!write_to_file(disasm))
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_disasm	disasm;

	ft_memset(&disasm, 0, sizeof(disasm));
	if (argc != 2)
	{
		write(2, "Usage: ./disasm [file.cor]\n", 28);
		return (1);
	}
	if (!start_disasm(&disasm, argv[1]))
		return (1);
	// printf("NAME: %s\nCOMMENT: %s\nPROG_LENGTH: %d\n", disasm.name, 
	// disasm.comment, disasm.prog_length);
	return (0);
}