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
	if (i < 2)
		return (error_line(ERR_FILE_NAME, NULL, 0));
	if (name[i] == 's' && name[i - 1] == '.')
	{
		asmb->filename = ft_strnew(length - 2); // ???  // ?
		ft_strncpy(asmb->filename, name, (length - 2));
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
    check_filename(argv[1], &asmb);
    if (!read_file(&asmb, argv[1]))
		return (1);
    // check_symbols();///////
    find_name_comment(&asmb);
    // parse_commands();
    // create_file();
    // write_to_file();
    return (0);
}