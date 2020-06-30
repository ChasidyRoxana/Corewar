/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:51:29 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/06/27 11:51:18 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	free_comm(t_asm *asmb)
{
	t_label	*tmp_lab;
	t_args	*tmp_arg;

	// int i = 1;
	while (asmb->comm)
	{
		// printf("free comm: %d\n", i++);//
		asmb->comm_last = asmb->comm;
		asmb->comm = asmb->comm->next;
		// int j = 1;
		while (asmb->comm_last->label)
		{
			// printf("	free label: %d\n", j++);//
			tmp_lab = asmb->comm_last->label;
			asmb->comm_last->label = asmb->comm_last->label->next;
			free(tmp_lab->line);
			free(tmp_lab);
		}
		// int k = 1;
		while (asmb->comm_last->args)
		{
			// printf("		free arg: %d\n", k++);//
			tmp_arg = asmb->comm_last->args;
			asmb->comm_last->args = asmb->comm_last->args->next;
			free(tmp_arg->arg_name);
			free(tmp_arg);
		}
	}
}

void		free_all(t_asm *asmb)
{
	free(asmb->filename);
	while (asmb->gnl)
	{
		// printf("!free gnl, nb_line: %d\n", asmb->gnl->nb_line);//
		asmb->gnl_last = asmb->gnl;
		asmb->gnl = asmb->gnl->next;
		free(asmb->gnl_last->line);
		free(asmb->gnl_last);
	}
	free_comm(asmb);
}

int			check_filename(char *name, t_asm *asmb)
{
	int		i;
	int		length;

	length = ft_strlen(name);
	i = length - 1;
	if (i < 1)
		return (error_common(ERR_FILE_NAME));
	if (name[i] == 's' && name[i - 1] == '.')
	{
		asmb->filename = ft_strnew(length + 2);
		ft_strncpy(asmb->filename, name, (length - 2));
		ft_strcat(asmb->filename, ".cor");
	}
	else
		return (error_common(ERR_FILE_NAME));
	return (1);
}

int			main(int argc, char **argv)
{
	t_asm	asmb;

	if (argc != 2)
	{
		write(2, "Usage: ./asm [file.s]\n", 23);
		return (1);
	}
	ft_memset(&asmb, 0, sizeof(asmb));
	if (!check_filename(argv[1], &asmb))
		return (1);
	if (!read_file(&asmb, argv[1]))
		return (1);
	if (!find_name_comment(&asmb))
		return (1);
	if (!parse_commands(&asmb))
		return (1);
	if (!write_to_file(&asmb))
		return (1);
	printf("The champion is ready\n");
	free_all(&asmb);
	return (0);
}
