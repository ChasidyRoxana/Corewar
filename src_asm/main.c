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

int     main(int argc, char **argv)
{
    t_asm	asmb;

    if (argc != 2)
    {
        write(2, "Usage: ./asm [file.s]\n", 23);
        return (1);
    }
	ft_memset(&asmb, 0, sizeof(asmb));
    // check_file_name();
    read_file(&asmb, argv[1]);
    // check_symbols();///////
    // find_name_comment();
    // parse_commands();
    // create_file();
    // write_to_file();
    return (0);
}