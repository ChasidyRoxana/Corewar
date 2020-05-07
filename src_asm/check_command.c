/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 13:25:40 by marvin            #+#    #+#             */
/*   Updated: 2020/05/07 18:22:12 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

// int			find_command(t_asm *asmb)
// {
// 	return (1);
// }

int			check_command(t_asm *asmb)
{
	int		i;
	char	*line;

	line = asmb->gnl_last->line;
	i = skip_first_spaces(line);
	if (line[i] == '\0' || line[i] == COMMENT_CHAR)
		return (1);
	if (!new_command(asmb))
		return (0);
	if (!find_label(asmb))
		return (0);
	
	// if (!find_command(asmb))
	// 	return (0);


	return (1);
}
