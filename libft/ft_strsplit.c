/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:11:41 by croxana           #+#    #+#             */
/*   Updated: 2020/01/07 17:07:50 by tpepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		if (*s != c)
			s++;
		else
		{
			while (*s == c)
				s++;
			count++;
		}
	}
	if (*(s - 1) != c)
		count++;
	return (count);
}

static size_t	ft_strf(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char		**ft_strfull(char const *s, char c, char **str, size_t size)
{
	size_t	j;
	size_t	i;

	j = 0;
	while (*s && j < size)
	{
		i = 0;
		while (*s == c)
			s++;
		if (!(str[j] = ft_strnew(ft_strf(s, c))))
		{
			while (i <= j)
				free(str[i++]);
			return (NULL);
		}
		while (*s != c && *s)
			str[j][i++] = *s++;
		str[j][i] = '\0';
		j++;
	}
	str[j] = NULL;
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_count(s, c);
	if (!(str = (char**)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	if (!(ft_strfull(s, c, str, size)))
	{
		free(str);
		return (NULL);
	}
	return (str);
}
