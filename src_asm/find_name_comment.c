/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_name_comment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 00:14:11 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/05/06 17:14:03 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

// return (0) - ошибка, (1) - все ок
int		check_next_line(t_asm *asmb, int j, t_gnl **tmp, int length)
{
	int i;

	i = 0;
	if (j < length)
        (length == PROG_NAME_LENGTH) ? (asmb->header.prog_name[j++] = '\n') : 
            (asmb->header.comment[j++] = '\n');
	while((*tmp)->line[i] && (*tmp)->line[i] != '\"')
	{
		if (length_error(j, length))
			return (0);
		(length == PROG_NAME_LENGTH) ? (asmb->header.prog_name[j++] = (*tmp)->line[i++]) : 
            (asmb->header.comment[j++] = (*tmp)->line[i++]);
	}
	if ((*tmp)->line[i] == '\"')
    {
		if (!check_end_space(&(*tmp)->line[i + 1]))
			return (0);
    }
	else if (*tmp == NULL)
		return (0);
	else
	{
		*tmp = (*tmp)->next;
		if (!check_next_line(asmb, j, tmp, length))
            return(0);
	}
	return (1);
}

// return (0) - ошибка, (1) - все ок
int		find_name(char *name, t_asm *asmb, t_gnl **tmp)
{
	int		i;
	int		j;

	j = 0;
    if(asmb->header.prog_name[0])
        return (0);
	i = skip_first_spaces(name);
	if (name[i] && name[i++] == '\"')
	{
		while (name[i] && name[i] != '\"')
		{
            if (length_error(j, PROG_NAME_LENGTH))
				return (0);
			asmb->header.prog_name[j++] = name[i++];
		}
		if (!name[i])
		{
			*tmp = (*tmp)->next;
			if (!check_next_line(asmb, j, tmp, PROG_NAME_LENGTH))
				return (0);
		}
        else 
        {
            if (!check_end_space(&name[i + 1]))
			    return (0);
        }
	}
	else
		return (0);
	printf("NAME .%s.\n", asmb->header.prog_name);
	return (1);
}

// return (0) - ошибка, (1) - все ок
int		find_comment(char *comment, t_asm *asmb, t_gnl **tmp)
{
	int		i;
	int		j;

	j = 0;
    if(asmb->header.comment[0])
        return (0);
	i = skip_first_spaces(comment);
	if (comment[i] && comment[i++] == '\"')
	{
		while (comment[i] && comment[i] != '\"')
		{
			if (length_error(j, COMMENT_LENGTH))
				return (0);
			asmb->header.comment[j++] = comment[i++];
		}
		if (!comment[i++])
		{   
            *tmp = (*tmp)->next;
			if (!check_next_line(asmb, j, tmp, COMMENT_LENGTH))
				return (0);
		}
        else 
        {
            if (!check_end_space(&comment[i + 1]))
			    return (0);
        }
	}
	else
		return (0);
	printf("COMMENT .%s.\n", asmb->header.comment);
	return (1);
}

// return (0) - ошибка, (1) - все ок
int		find_name_comment(t_asm *asmb)
{
	t_gnl	*tmp;
	int		flag;
    int     i;

	tmp = asmb->gnl;
	flag = 0;
	while (tmp) 
	{
        if (flag == 2)
			return (1);
        i = skip_first_spaces(tmp->line);
		if (tmp->line[i] == '.')
		{
            if (ft_strcmp(tmp->line + i, NAME_CMD_STRING) > 0) // ? проверяем .name (не знаю какой функцией лучше)
            {
                if (!find_name(tmp->line + i + ft_strlen(NAME_CMD_STRING), asmb, &tmp))
                    return(error_line(ERR_NAME, tmp, 0));
            }
			else if (ft_strcmp(tmp->line + i, COMMENT_CMD_STRING) > 0) // ? проверяем .comment (не знаю какой функцией лучше)
            {
				if (!find_comment(tmp->line + i + ft_strlen(COMMENT_CMD_STRING), asmb, &tmp))
                    return(error_line(ERR_COMMENT, tmp, 0));
            }
            else
                return (0);
			flag++;
		}
		else if (tmp->line[i] != COMMENT_CHAR && tmp->line[i] != COMMENT_CHAR_2)
			return (0);
		tmp = tmp->next;
	}
	return(0);
}