/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 21:45:43 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/07 21:48:41 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int     error_vm(int error)
{
    if (error == ERR_FILE_NAME)
        write(2, "The champion file should be named [filename].cor\n", 50);
    else if (error == ERR_MAX_PLAYERS)
        write(2, "Too many champions\n", 20);
    else if (error == ERR_FLAG)
        write(2, "Error with flags?\nUsage: ...", 29);
    return (0);
}