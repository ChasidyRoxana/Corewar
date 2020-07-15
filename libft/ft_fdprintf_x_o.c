/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf_x_o.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:30:12 by marvin            #+#    #+#             */
/*   Updated: 2020/07/15 18:30:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_else(t_form *pt, char *s, int n, unsigned long li)
{
	if (pt->zero != 1 || (pt->zero == 1 && pt->precision != -1))
		ft_print_sp(pt, (pt->hash == 1 && li != 0 ? pt->width - n - 2 :
		pt->width - n), 32);
	if (li != 0 && pt->hash == 1)
		ft_fdprintf(pt->fd, "0%c", pt->format[pt->i]);
	if (pt->zero == 1 && pt->precision == -1)
		ft_print_sp(pt, (pt->hash == 1 && li != 0 ? pt->width - n - 2 :
		pt->width - n), 48);
	write(pt->fd, s, n);
}

static int	ft_print_str_x(t_form *pt, char *s, unsigned long li)
{
	int	n;

	n = ft_strlen(s);
	if (pt->precision == 0)
		return (ft_print_sp(pt, pt->width, ' '));
	if (pt->minus == 1)
	{
		if (li != 0 && pt->hash == 1)
			ft_fdprintf(pt->fd, "0%c", pt->format[pt->i]);
		write(pt->fd, s, n);
		ft_print_sp(pt, (pt->hash == 1 && li != 0 ? pt->width - n - 2 :
		pt->width - n), 32);
	}
	else
		ft_else(pt, s, n, li);
	return (1);
}

int			ft_fdprintf_x(t_form *pt)
{
	unsigned long int	li;
	unsigned long int	li2;
	char				*s;
	int					i;

	ft_length_u(pt, &li);
	li2 = li;
	i = ft_count_b(li, 4);
	s = ft_strnew(li == 0 ? 1 : i);
	if (li == 0)
		s[0] = '0';
	while (li > 0)
	{
		if (pt->format[pt->i] == 'X')
			s[--i] = (li % 16 > 9) ? li % 16 + 55 : li % 16 + '0';
		else if (pt->format[pt->i] == 'x')
			s[--i] = (li % 16 > 9) ? li % 16 + 'W' : li % 16 + '0';
		li >>= 4;
	}
	ft_check_prec(pt, &s, 'l');
	ft_print_str_x(pt, s, li2);
	free(s);
	return (1);
}

static int	ft_print_str_o(t_form *pt, char *s, unsigned long lo)
{
	int	n;

	if ((n = ft_strlen(s)) == 0)
		n = 1;
	if (pt->precision == 0 && pt->hash == 0)
		return (ft_print_sp(pt, pt->width, 32));
	if (pt->minus != 1)
		if (pt->zero != 1 || (pt->zero == 1 && pt->precision != -1))
			ft_print_sp(pt, (pt->hash == 1 && s[0] != '0' ? pt->width - n - 1 :
			pt->width - n), 32);
	if (pt->hash == 1 && s[0] != '0')
		write(pt->fd, "0", 1);
	if (pt->minus != 1 && pt->zero == 1 && pt->precision == -1)
		ft_print_sp(pt, (pt->hash == 1 && lo != 0 ? pt->width - n - 1 :
		pt->width - n), 48);
	write(pt->fd, s, n);
	if (pt->minus == 1)
		ft_print_sp(pt, (pt->hash == 1 && s[0] != '0' ? pt->width - n - 1 :
		pt->width - n), 32);
	return (1);
}

int			ft_fdprintf_o(t_form *pt)
{
	unsigned long int	lo;
	unsigned long int	lo2;
	char				*s;
	int					i;

	ft_length_u(pt, &lo);
	lo2 = lo;
	i = ft_count_b(lo, 3);
	s = ft_strnew(lo == 0 ? 1 : i);
	if (lo == 0)
		s[0] = '0';
	while (lo > 0)
	{
		s[--i] = lo % 8 + '0';
		lo >>= 3;
	}
	ft_check_prec(pt, &s, 'l');
	ft_print_str_o(pt, s, lo2);
	free(s);
	return (1);
}
