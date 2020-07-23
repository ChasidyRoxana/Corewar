/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:51:29 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/24 00:30:39 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	free_comm(t_asm *asmb)
{
	t_label	*tmp_lab;
	t_args	*tmp_arg;

	while (asmb->comm)
	{
		asmb->comm_last = asmb->comm;
		asmb->comm = asmb->comm->next;
		while (asmb->comm_last->label)
		{
			tmp_lab = asmb->comm_last->label;
			asmb->comm_last->label = asmb->comm_last->label->next;
			free(tmp_lab->line);
			free(tmp_lab);
		}
		while (asmb->comm_last->args)
		{
			tmp_arg = asmb->comm_last->args;
			asmb->comm_last->args = asmb->comm_last->args->next;
			free(tmp_arg->arg_name);
			free(tmp_arg);
		}
		free(asmb->comm_last);
	}
}

static void	free_all(t_asm *asmb)
{
	if (asmb->filename)
		free(asmb->filename);
	while (asmb->gnl)
	{
		asmb->gnl_last = asmb->gnl;
		asmb->gnl = asmb->gnl->next;
		free(asmb->gnl_last->line);
		free(asmb->gnl_last);
	}
	free_comm(asmb);
}

static int	check_filename(char *name, t_asm *asmb)
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
		ft_fdprintf(2, "Usage: ./asm [file.s]\n");
		return (1);
	}
	ft_memset(&asmb, 0, sizeof(asmb));
	if (check_filename(argv[1], &asmb) &&
		read_file(&asmb, argv[1]) &&
		find_name_comment(&asmb) &&
		delete_empty_lines(&asmb) &&
		parse_commands(&asmb) &&
		write_to_file(&asmb))
		ft_printf("The champion is ready\n");
	free_all(&asmb);
	return (0);
}
