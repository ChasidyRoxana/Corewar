/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:28:21 by croxana           #+#    #+#             */
/*   Updated: 2019/04/14 19:13:39 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	r;
	size_t	t;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	r = 0;
	t = i;
	if (i >= size)
		return (j + size);
	while (src[r] && t < size - 1)
		dst[t++] = src[r++];
	dst[t] = '\0';
	return (i + j);
}
