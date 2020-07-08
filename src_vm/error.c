/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 21:45:43 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/08 15:21:10 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int     error_line(int error, char *str)
{
    if (error == ERR_OPEN_FILE)
        printf("Can't read source file %s\n", str);
    return (0);
}

int     error_vm(int error)
{
    if (error == ERR_FILE_NAME)
        write(2, "The champion file should be named [filename].cor\n", 50);
    else if (error == ERR_MAX_PLAYERS)
        write(2, "Too many champions\n", 20);
    else if (error == ERR_FLAG)
        write(2, "Error with flags?\nUsage: ...", 29);
    else if (error == ERR_MAGIC_HEADER)
        write(2, "Wrong magic header\n", 20);
    else if (error == ERR_NAME)
        write(2, "Error with champion name\n", 26);
    else if (error == ERR_COMMENT)
        write(2, "Error with champion comment\n", 29);
    else if (error == ERR_MAX_SIZE)
        write(2, "The champion size is too big\n", 30);
    else if (error == ERR_CHAMP_SIZE)
        write(2, "Wrong champion size\n", 21);
    return (0);
}