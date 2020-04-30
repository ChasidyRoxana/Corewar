/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:05:25 by croxana           #+#    #+#             */
/*   Updated: 2019/10/14 13:21:19 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *nee, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (*nee == '\0')
		return ((char *)hay);
	while (*hay && n < len)
	{
		if (*hay == *nee)
		{
			while (nee[i] && hay[i] == nee[i])
				i++;
			if (!(nee[i]) && (n + i) <= len)
				return ((char *)hay);
			i = 0;
		}
		hay++;
		n++;
	}
	return (NULL);
}
