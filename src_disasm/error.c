/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:10:46 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/02 14:13:08 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disasm.h"

int     error_disasm(int error)
{
    if (error == ERR_FILE_NAME)
        write(2, "Use [filename].cor\n", 20);
    return (0);
}