/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 12:02:01 by croxana           #+#    #+#             */
/*   Updated: 2020/03/02 14:49:12 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_end(char **line, char **buf)
{
	char	*tp;
	char	*tmp;

	tp = ft_strchr(*buf, '\n');
	if (tp)
	{
		*line = ft_strcdup(*buf, '\n');
		tmp = *buf;
		*buf = ft_strdup(&tp[1]);
		free(tmp);
		return (2);
	}
	else if (ft_strlen(*buf) > 0)
	{
		*line = ft_strcdup(*buf, '\n');
		free(*buf);
		*buf = 0;
		return (1);
	}
	free(*buf);
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*buf[FD_SIZE];
	int			k;
	char		a[BUFF_SIZE + 1];
	char		*join;

	if (fd < 0 || fd > FD_SIZE || read(fd, a, 0) == -1)
		return (-1);
	if (!buf[fd] && !(buf[fd] = ft_strnew(0)))
		return (-1);
	while (!ft_strchr(buf[fd], '\n'))
	{
		k = read(fd, a, BUFF_SIZE);
		if (k == 0)
			break ;
		a[k] = '\0';
		join = ft_strjoin(buf[fd], a);
		free(buf[fd]);
		buf[fd] = join;
	}
	return (ft_end(line, &buf[fd]));
}
