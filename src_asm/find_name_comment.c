/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_name_comment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 00:14:11 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/05/05 14:16:05 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

// return (0) - ошибка, (1) - все ок
int		check_next_line(t_asm *asmb, int j, t_gnl **tmp, int length)
{
	int i;

	i = 0;
    // если у нас еще осталось место (нет переполнения), записываем \n,
    // так как мы уже смотрим и записываем новую строку.
    // Т.к. эта функция и для имени, и для коммента - записываем либо в prog_name, либо в comment
	if (j < length)
        (length == PROG_NAME_LENGTH) ? (asmb->header.prog_name[j++] = '\n') : 
            (asmb->header.comment[j++] = '\n');
    // пока не дойдем до конца строки или до закрывающей кавычки
	while((*tmp)->line[i] && (*tmp)->line[i] != '\"')
	{
        // проверяем на переполнение имени или коммента
		if (length_error(j, length))
			return (0);
        // если место есть, заполняем имя или коммент
		(length == PROG_NAME_LENGTH) ? (asmb->header.prog_name[j++] = (*tmp)->line[i++]) : 
            (asmb->header.comment[j++] = (*tmp)->line[i++]);
	}
    // если дошли до закрывающей кавычки, проверяем есть ли после нее какие-либо символы,
    // кроме пробелов или табов. если есть - это ошибка
	if ((*tmp)->line[i] == '\"')
    {
		if (!check_end_space(&(*tmp)->line[i + 1]))
			return (0);
    }
    // если по всем строкам уже прошлись и не нашли кавычку
	else if (*tmp == NULL)
		return (0);
    // если дошли до конца строки и не нашли кавычку - 
    // переходим на след строку и снова записыываем/проверяем
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
    // если у нас уже что-то записано в имени - ошибка, выходим
    if(asmb->header.prog_name[0])
        return (0);
    // скипаем пробелы и табы в начале строки
	i = skip_first_spaces(name);
    // проверяем, есть ли открывающая кавычка
	if (name[i] && name[i++] == '\"')
	{
		while (name[i] && name[i] != '\"')
		{
			// чекаем, не переполнен ли prog_name
            if (length_error(j, PROG_NAME_LENGTH))
				return (0);
            // записываем
			asmb->header.prog_name[j++] = name[i++];
		}
        // если мы записали, все что было в строке, но не было закрывающей кавычки,
        // то проверяем и записываем следующую строку (пока не найдем закрывающую кавычку)
        // или не выйдем с ошибкой
		if (!name[i])
		{
            // переход на следующую строку
			*tmp = (*tmp)->next;
            // рекурсивная функция, которая записывает строку, ищет закрывающую кавычку
			if (!check_next_line(asmb, j, tmp, PROG_NAME_LENGTH))
				return (0);
		}
        // если у нас была закрыващая кавычка
        else 
        {
            // проверяем, что после кавычки нет никаких символов, кроме пробелов и табов
            if (!check_end_space(&name[i + 1]))
			    return (0);
        }
	}
	else // если у нас не было открывающей кавычки
		return (0);
	printf("NAME .%s.\n", asmb->header.prog_name);
	return (1);
}

// return (0) - ошибка, (1) - все ок
// тут все так же, как в find_name, только записываем в asmb->header.comment
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
    // проходимся по строкам
	while (tmp) 
	{
        // если нашли и .name, и .comment - все ок, выходим
        if (flag == 2)
			return (1);
        // скипаем пробелы и табы в начале строки
        i = skip_first_spaces(tmp->line);
        // если первый символ в строке - точка, ищем .name и .comment
		if (tmp->line[i] == '.')
		{
            if (ft_strcmp(tmp->line + i, NAME_CMD_STRING) > 0) // ? проверяем .name (не знаю какой функцией лучше)
            {
				// проверяем имя в отдельной функции - отправляем туда строку без .name
                if (!find_name(tmp->line + i + ft_strlen(NAME_CMD_STRING), asmb, &tmp))
                    // если что-то не так с именем - выводим ошибку и строку, в которой была эта ошибка
                    return(error_name_comment(NAME_CMD_STRING, tmp->nb_line));
            }
			else if (ft_strcmp(tmp->line + i, COMMENT_CMD_STRING) > 0) // ? проверяем .comment (не знаю какой функцией лучше)
            {
                // проверяем имя в отдельной функции - отправляем туда строку без .comment
				if (!find_comment(tmp->line + i + ft_strlen(COMMENT_CMD_STRING), asmb, &tmp))
                    // если что-то не так с комментом - выводим ошибку и строку, в которой была эта ошибка
                    return(error_name_comment(COMMENT_CMD_STRING, tmp->nb_line));
            }
            else // если есть точка, но это не .name и не .comment
                return (0);
            // если все ок - плюсуем флаг (нашли .comment/.name)
			flag++;
		}
		else if (tmp->line[i] != COMMENT_CHAR && tmp->line[i] != COMMENT_CHAR_2) // если в начале строки нет '.', '#' или ';' - ошибка
			return (0);
        // переходим к следующей строке
		tmp = tmp->next;
	}
	return(0);
}

// если два имени/два коммента