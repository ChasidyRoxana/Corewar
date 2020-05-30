/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 15:02:42 by marvin            #+#    #+#             */
/*   Updated: 2020/05/30 19:01:04 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/* создаёт новый элемент списка команд, заполняет его нулями, ставит *prev,
** при ошибке возвращает 0
*/
int			new_command(t_asm *asmb)
{
	t_command	*tmp;

	tmp = NULL;
	if (!asmb->comm)
	{
		if (!(asmb->comm = (t_command*)malloc(sizeof(t_command))))
			return (error_line(ERR_MALLOC, NULL, 0));
		asmb->comm_last = asmb->comm;
	}
	else
	{
		if (!(asmb->comm_last->next = (t_command*)malloc(sizeof(t_command))))
			return (error_line(ERR_MALLOC, NULL, 0));
		tmp = asmb->comm_last;
		asmb->comm_last = asmb->comm_last->next;
	}
	ft_memset((void*)asmb->comm_last, 0, sizeof(t_command));
	asmb->comm_last->prev = tmp;
	asmb->comm_last->label_line = NULL; // на всякий случай (?)
	return (1);
}

/* при ошибке возвращает 0
*/
int		parse_commands(t_asm *asmb)
{
	while (asmb->gnl_last)
	{
		if (!check_command(asmb))
			return (0);
		asmb->gnl_last = asmb->gnl_last->next;
	}
	if (!check_comm_list(asmb))
		return (0);

	// для чего это?
	// while (asmb->comm_last->label)
	// {
	// 	printf("\nCheckLabel: .%s.\n", asmb->comm_last->label->line);
	// 	asmb->comm_last->label = asmb->comm_last->label->next; 
	// }
		// create_command();
	// printf("%d\n", asmb->gnl->nb_line);
	
	// for check
	// int j = 0;
	// t_label	*temp;
	// t_command *tmp = asmb->comm;
	// while(tmp){
	// 	j++;
	// 	temp = tmp->label;
	// 	while(temp)
	// 	{
	// 		printf("%s\n", temp->line);
	// 		temp = temp->next;
	// 	}
	// 	tmp = tmp->next;
	// }
	// printf("%d command\n", j);
	return (1);
}
