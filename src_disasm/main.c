/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:59:03 by tpepperm          #+#    #+#             */
/*   Updated: 2020/07/16 21:42:52 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

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

/*
**	проверяем, что у нас файл "*.cor" (то есть хотя бы
**	один символ и расширение .cor)
*/

static int	check_filename(t_disasm *disasm, char *name)
{
	int			length;

	length = ft_strlen(name);
	if (length < 5)
		return (error_disasm(ERR_FILE_NAME));
	if (ft_strcmp(&name[length - 4], ".cor") == 0)
	{
		disasm->filename = ft_strnew(length + 2);
		ft_strncpy(disasm->filename, "new_", 4);
		ft_strncat(disasm->filename, name, (length - 4));
		ft_strcat(disasm->filename, ".s");
	}
	else
		return (error_disasm(ERR_FILE_NAME));
	return (1);
}

int			main(int argc, char **argv)
{
	t_disasm	disasm;

	ft_memset(&disasm, 0, sizeof(disasm));
	if (argc != 2)
		return (error_disasm(ERR_USAGE));
	if (check_filename(&disasm, argv[1]) &&
		parse_file(&disasm, argv[1]) &&
		write_to_file(&disasm))
		write(1, "The .s file is ready\n", 22);
	free_all(&disasm);
	return (0);
}
