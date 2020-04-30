/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:14:29 by croxana           #+#    #+#             */
/*   Updated: 2019/04/27 11:48:33 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d1;
	char	*s1;
	char	*d2;
	char	*s2;
	size_t	i;

	i = 0;
	d1 = (char *)dst;
	s1 = (char *)src;
	d2 = (char *)(dst - 1 + len);
	s2 = (char *)(src - 1 + len);
	if (dst == src)
		return (dst);
	if (s1 > d1)
		while (i++ < len)
			*d1++ = *s1++;
	else
		while (i++ < len)
			*d2-- = *s2--;
	return (dst);
}
