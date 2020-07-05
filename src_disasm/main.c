/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 23:19:46 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/05 18:40:35 by tkarpukova       ###   ########.fr       */
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

int		main(int argc, char **argv)
{
	t_disasm	disasm;

	ft_memset(&disasm, 0, sizeof(disasm));
	if (argc != 2)
	{
		write(2, "Usage: ./disasm [file.cor]\n", 28);
		return (1);
	}
	if (start_disasm(&disasm, argv[1]) &&
		write_to_file(&disasm))
	printf("The .s file is ready\n");
	free_all(&disasm);
	return (0);
}