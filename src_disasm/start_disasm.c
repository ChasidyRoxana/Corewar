/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_disasm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 18:40:45 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/05 18:40:59 by tkarpukova       ###   ########.fr       */
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
	return (1);
}