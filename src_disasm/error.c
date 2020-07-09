/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:10:46 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/09 15:46:05 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

int     error_disasm(int error)
{
    if (error == ERR_FILE_NAME)
        write(2, "Use [filename].cor\n", 20);
    else if (error == ERR_CREATE_FILE)
        write(2, "Could not CREATE/OPEN file\n", 28);
    return (0);
}