/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf_di.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:58:21 by marvin            #+#    #+#             */
/*   Updated: 2020/07/15 17:58:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_length(t_form *pt, long *l)
{
	if (pt->hh == 1)
		*l = (long)(char)va_arg(*(pt->ptr), int);
	else if (pt->h == 1)
		*l = (long)(short int)va_arg(*(pt->ptr), int);
	else if (pt->ll == 1 || pt->l == 1)
		*l = va_arg(*(pt->ptr), long);
	else
		*l = (long)va_arg(*(pt->ptr), int);
}

static void	ft_continue(t_form *pt, char *s, long l, int n)
{
	if (pt->minus != 1)
		if (pt->zero != 1 || (pt->zero == 1 && pt->precision != -1))
			ft_print_sp(pt, (l < 0 || pt->plus == 1 || pt->space == 1 ?
			pt->width - n - 1 : pt->width - n), 32);
	if (l < 0)
		write(pt->fd, "-", 1);
	if ((pt->plus == 1 || pt->space == 1) && l >= 0)
		write(pt->fd, (pt->plus == 1 ? "+" : " "), 1);
	if (pt->minus != 1 && pt->zero == 1 && pt->precision == -1)
		ft_print_sp(pt, (l < 0 || pt->plus == 1 || pt->space == 1 ?
		pt->width - n - 1 : pt->width - n), 48);
	write(pt->fd, s, n);
	if (pt->minus == 1)
		ft_print_sp(pt, (l < 0 || pt->plus == 1 || pt->space == 1 ?
		pt->width - n - 1 : pt->width - n), 32);
}

static int	ft_print_str(t_form *pt, char *s, long l)
{
	int	n;

	if ((n = ft_strlen(s)) == 0)
		n = 1;
	if (pt->precision == 0)
	{
		if (pt->minus != 1)
			ft_print_sp(pt, (l < 0 || pt->plus == 1 || pt->space == 1 ?
			pt->width - 1 : pt->width), 32);
		if (l < 0)
			write(pt->fd, "-", 1);
		if (l >= 0 && (pt->plus == 1 || pt->space == 1))
			write(pt->fd, (pt->plus == 1 ? "+" : " "), 1);
		if (pt->minus == 1)
			ft_print_sp(pt, (l < 0 || pt->plus == 1 || pt->space == 1 ?
			pt->width - 1 : pt->width), 32);
		return (1);
	}
	ft_continue(pt, s, l, n);
	return (1);
}

int			ft_fdprintf_di(t_form *pt)
{
	long int	l;
	char		*s;

	ft_length(pt, &l);
	s = ft_itoa_l(l);
	ft_check_prec(pt, &s, 'l');
	ft_print_str(pt, s, l);
	free(s);
	return (1);
}
