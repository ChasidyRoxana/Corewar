/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 17:40:49 by marvin            #+#    #+#             */
/*   Updated: 2020/06/27 11:28:07 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int		create_file(t_asm *asmb, int *fd)
{
//разобраться с дефайнами и циферкой
	if ((*fd = open(asmb->filename, O_CREAT | O_TRUNC | O_RDWR, 755)) == -1)
		return (0);
	if (*fd != -1 && (*fd = open(asmb->filename, O_RDWR)) == -1)
		// if ((fd = open(name, O_RDWR)) == -1)
		return (0);
	return (1);
}

int		write_to_file(t_asm *asmb)
{
	int		fd;

	if (!create_file(asmb, &fd))
		return (0);
	// write(fd, (unsigned char*)&asmb->header, sizeof(asmb->header));
	close(fd);
	return (1);
}
