/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:06:33 by croxana           #+#    #+#             */
/*   Updated: 2019/04/25 19:58:23 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src, int c,
		size_t n)
{
	unsigned char	*d1;
	unsigned char	*s1;
	size_t			i;
	unsigned char	d;

	d1 = (unsigned char *)dst;
	s1 = (unsigned char *)src;
	i = 0;
	d = (unsigned char)c;
	while (i < n && s1[i] != d)
	{
		d1[i] = s1[i];
		i++;
	}
	if (i < n && s1[i] == d)
	{
		d1[i] = s1[i];
		return (d1 + i + 1);
	}
	return (NULL);
}
