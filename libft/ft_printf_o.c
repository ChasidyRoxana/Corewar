/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_o.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 13:04:51 by croxana           #+#    #+#             */
/*   Updated: 2020/02/11 14:53:25 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_str(t_form *pt, char *s, unsigned long lo)
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
		write(1, "0", 1);
	if (pt->minus != 1 && pt->zero == 1 && pt->precision == -1)
		ft_print_sp(pt, (pt->hash == 1 && lo != 0 ? pt->width - n - 1 :
		pt->width - n), 48);
	write(1, s, n);
	if (pt->minus == 1)
		ft_print_sp(pt, (pt->hash == 1 && s[0] != '0' ? pt->width - n - 1 :
		pt->width - n), 32);
	return (1);
}

int			ft_printf_o(t_form *pt)
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
	ft_print_str(pt, s, lo2);
	free(s);
	return (1);
}
