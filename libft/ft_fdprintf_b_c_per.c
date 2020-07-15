/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf_b_c_per.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpepperm <tpepperm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:52:21 by marvin            #+#    #+#             */
/*   Updated: 2020/07/15 22:05:43 by tpepperm         ###   ########.fr       */
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

int			ft_fdprintf_b(t_form *pt)
{
	long	n;
	int		i;

	i = ft_type(pt, &n);
	while (--i >= 0)
	{
		write(pt->fd, ((1 & (n >> i)) == 1 ? "1" : "0"), 1);
		if (i != 0 && i % 4 == 0)
			write(pt->fd, " ", 1);
	}
	return (1);
}

int			ft_fdprintf_c(t_form *pt)
{
	int c;

	c = va_arg(*(pt->ptr), int);
	if (pt->minus != 1)
		ft_print_sp(pt, pt->width - 1, ' ');
	write(pt->fd, &c, 1);
	if (pt->minus == 1)
		ft_print_sp(pt, pt->width - 1, ' ');
	return (1);
}

int			ft_fdprintf_per(t_form *pt)
{
	if (pt->minus != 1)
	{
		if (pt->zero == 1)
			ft_print_sp(pt, pt->width - 1, '0');
		else
			ft_print_sp(pt, pt->width - 1, ' ');
	}
	write(pt->fd, "%%", 1);
	if (pt->minus == 1)
		ft_print_sp(pt, pt->width - 1, ' ');
	return (1);
}
