/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 12:58:04 by croxana           #+#    #+#             */
/*   Updated: 2019/11/28 15:51:27 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_type(t_form *pt, long *n)
{
	int	i;

	if (pt->l == 1 || pt->ll == 1)
	{
		i = 32;
		*n = va_arg(*(pt->ptr), long int);
	}
	else if (pt->h == 1)
	{
		i = 8;
		*n = (long)(short int)va_arg(*(pt->ptr), int);
	}
	else if (pt->hh == 1)
	{
		i = 4;
		*n = (long)(char)va_arg(*(pt->ptr), int);
	}
	else
	{
		i = 16;
		*n = va_arg(*(pt->ptr), int);
	}
	return (i);
}

int			ft_printf_b(t_form *pt)
{
	long	n;
	int		i;

	i = ft_type(pt, &n);
	while (--i >= 0)
	{
		write(1, ((1 & (n >> i)) == 1 ? "1" : "0"), 1);
		if (i != 0 && i % 4 == 0)
			write(1, " ", 1);
	}
	return (1);
}
