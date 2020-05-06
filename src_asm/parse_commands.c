/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 15:02:42 by marvin            #+#    #+#             */
/*   Updated: 2020/05/06 21:12:54 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"


int		find_label() 
{
	
}

/* при ошибке возвращает 0
*/
int		parse_commands(t_asm *asmb)
{
	// t_gnl	*tmp_gnl;
	find_label(); // разобрать метки и команды
	// check_command(); // find_first_word();
	// create_command();
	printf("%d\n", asmb->gnl->nb_line);
	return (1);
}
