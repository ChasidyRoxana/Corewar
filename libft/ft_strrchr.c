/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:23:11 by croxana           #+#    #+#             */
/*   Updated: 2019/04/21 20:16:46 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		n;

	i = 0;
	n = -1;
	while (s[i])
	{
		if (s[i] == c)
			n = i;
		i++;
	}
	if (!(s[i]) && c == '\0')
		return ((char*)(s + i));
	if (n > -1)
		return ((char*)(s + n));
	return (NULL);
}
