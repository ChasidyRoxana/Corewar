/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 23:19:46 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/05 13:48:09 by tkarpukova       ###   ########.fr       */
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

static void	free_all(t_disasm *disasm)
{
	t_arg	*tmp;

	if (disasm->filename)
		free(disasm->filename);
	while (disasm->ops)
	{
		disasm->ops_last = disasm->ops;
		disasm->ops = disasm->ops->next;
		while (disasm->ops_last->args)
		{
			tmp = disasm->ops_last->args;
			disasm->ops_last->args = disasm->ops_last->args->next;
			free(tmp);
		}
		free(disasm->ops_last);
	}
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
	if (start_disasm(&disasm, argv[1])&&
		write_to_file(&disasm))
	printf("The .s file is ready\n");
	free_all(&disasm);
	return (0);
}