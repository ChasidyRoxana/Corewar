   /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 16:51:29 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/05/04 17:00:50 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int			check_filename(char *name, t_asm *asmb) 
{
	int		i;
	int		length;

    length = ft_strlen(name);
	i = length - 1;
	if (i < 1)
		return (error_line(ERR_FILE_NAME, NULL, 0));
	if (name[i] == 's' && name[i - 1] == '.')
	{
		asmb->filename = ft_strnew(length + 2);
		ft_strncpy(asmb->filename, name, (length - 2));
		ft_strcat(asmb->filename, ".cor");
	}
	else
		return (error_line(ERR_FILE_NAME, NULL, 0));
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
	printf("GNL_LAST: %s\n", asmb.gnl_last->line);
    if (!parse_commands(&asmb))
		return (1);
    // write_to_file(); // create_file() перед записью и создадим
    return (0);
}