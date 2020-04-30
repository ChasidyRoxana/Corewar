/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 12:16:23 by croxana           #+#    #+#             */
/*   Updated: 2020/01/07 17:24:02 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_num_color(char *s)
{
	if (ft_strstr(s, "red") != NULL)
		return ('1');
	else if (ft_strstr(s, "green") != NULL)
		return ('2');
	else if (ft_strstr(s, "yellow") != NULL)
		return ('3');
	else if (ft_strstr(s, "blue") != NULL)
		return ('4');
	else if (ft_strstr(s, "magenta") != NULL)
		return ('5');
	else if (ft_strstr(s, "cyan") != NULL)
		return ('6');
	else if (ft_strstr(s, "white") != NULL)
		return ('7');
	else
		return ('0');
}

static char	*ft_color(char *s, char tmp[])
{
	int	i;

	i = 0;
	while (tmp[i] != '\0')
		i++;
	if (ft_strstr(s, "back") != NULL)
	{
		if (ft_strstr(&s[5], "bright") != NULL)
		{
			tmp[i++] = '1';
			tmp[i++] = '0';
		}
		else
			tmp[i++] = '4';
	}
	else if (ft_strstr(s, "bright") != NULL)
		tmp[i++] = '9';
	else if (ft_strstr(s, "eoc") == NULL)
		tmp[i++] = '3';
	tmp[i++] = ft_num_color(s);
	tmp[i] = 'm';
	return (tmp);
}

static char	*ft_find_s(t_form *pt, char *s)
{
	int		i;

	i = pt->i;
	while (pt->format[i] != '\0' && pt->format[i] != '}' &&
		pt->format[i] != '%')
		i++;
	if (pt->format[i] == '%' && pt->format[i + 1] == 's')
	{
		s = ft_strdup(va_arg(*(pt->ptr), char*));
		while (pt->format[pt->i] != '\0' && pt->format[pt->i] != '}')
			pt->i++;
	}
	else
	{
		s = ft_strnew(i - (pt->i));
		i = 0;
		while (pt->format[pt->i] != '\0' && pt->format[pt->i] != '}')
			s[i++] = pt->format[pt->i++];
	}
	return (s);
}

int			ft_printf_color(t_form *pt)
{
	int		i;
	char	*s;
	char	tmp[7];

	s = NULL;
	pt->i++;
	s = ft_find_s(pt, s);
	i = 0;
	while (i < 7)
		tmp[i++] = '\0';
	tmp[0] = '\x1b';
	tmp[1] = '[';
	write(1, ft_color(s, tmp), ft_strlen(tmp));
	free(s);
	pt->j = pt->i;
	return (0);
}
