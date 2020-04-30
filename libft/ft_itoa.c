/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:13:33 by croxana           #+#    #+#             */
/*   Updated: 2019/04/20 13:39:38 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(size_t n)
{
	size_t	count;

	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char		*ft_strfill(char *str, int num, int i, int flag)
{
	i--;
	if (flag < 0)
		str[0] = '-';
	while (num > 0)
	{
		str[i--] = num % 10 + 48;
		num /= 10;
	}
	return (str);
}

char			*ft_itoa(int n)
{
	int		flag;
	int		i;
	char	*str;

	flag = 0;
	i = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == MIN_INT)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		flag = -1;
		n = -n;
		i = 1;
	}
	i = i + ft_count(n);
	if (!(str = ft_strnew(i)))
		return (NULL);
	return (i == 0 ? str : ft_strfill(str, n, i, flag));
}
