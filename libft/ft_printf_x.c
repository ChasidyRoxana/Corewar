/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 14:10:19 by croxana           #+#    #+#             */
/*   Updated: 2019/10/14 13:46:55 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_else(t_form *pt, char *s, int n, unsigned long li)
{
	if (pt->zero != 1 || (pt->zero == 1 && pt->precision != -1))
		ft_print_sp((pt->hash == 1 && li != 0 ? pt->width - n - 2 :
		pt->width - n), 32);
	if (li != 0 && pt->hash == 1)
		ft_printf("0%c", pt->format[pt->i]);
	if (pt->zero == 1 && pt->precision == -1)
		ft_print_sp((pt->hash == 1 && li != 0 ? pt->width - n - 2 :
		pt->width - n), 48);
	write(1, s, n);
}

static int	ft_print_str(t_form *pt, char *s, unsigned long li)
{
	int	n;

	n = ft_strlen(s);
	if (pt->precision == 0)
		return (ft_print_sp(pt->width, ' '));
	if (pt->minus == 1)
	{
		if (li != 0 && pt->hash == 1)
			ft_printf("0%c", pt->format[pt->i]);
		write(1, s, n);
		ft_print_sp((pt->hash == 1 && li != 0 ? pt->width - n - 2 :
		pt->width - n), 32);
	}
	else
		ft_else(pt, s, n, li);
	return (1);
}

int			ft_printf_x(t_form *pt)
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
	ft_print_str(pt, s, li2);
	free(s);
	return (1);
}
