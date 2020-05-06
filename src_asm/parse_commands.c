/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 15:02:42 by marvin            #+#    #+#             */
/*   Updated: 2020/05/06 17:58:03 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/* при ошибке возвращает 0
*/
int			parse_commands(t_asm *asmb)
{
	// t_gnl	*tmp_gnl;
	find_label();
	check_command(); // find_first_word();
	create_command();
	printf("%d\n", asmb->gnl->nb_line);
	return (1);
}
