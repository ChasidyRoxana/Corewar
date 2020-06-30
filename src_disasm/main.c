/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 23:19:46 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/06/30 23:42:59 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

// int			check_filename(char *name, t_asm *asmb)
// {
// 	int		i;
// 	int		length;

// 	length = ft_strlen(name);
// 	i = length - 1;
// 	if (i < 1)
// 		return (error_common(ERR_FILE_NAME));
// 	if (name[i] == 's' && name[i - 1] == '.')
// 	{
// 		asmb->filename = ft_strnew(length + 2);
// 		ft_strncpy(asmb->filename, name, (length - 2));
// 		ft_strcat(asmb->filename, ".cor");
// 	}
// 	else
// 		return (error_common(ERR_FILE_NAME));
// 	return (1);
// }

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Usage: ./disasm [file.cor]\n", 28);
		return (1);
	}
	// проверяем .cor
	check_filename();
	// парсим файл и записываем все в структуру
	parse_file();
	// записываем данные из структуры в файл
	write_to_file();
	return (0);
}