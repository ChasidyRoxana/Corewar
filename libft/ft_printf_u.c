/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 13:47:12 by croxana           #+#    #+#             */
/*   Updated: 2019/10/14 13:46:53 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_num(unsigned long lu2)
{
	int	i;

	i = 0;
	while (lu2 > 0)
	{
		lu2 /= 10;
		i++;
	}
	return (i);
}

static int	ft_print_str(t_form *pt, char *s)
{
	int	n;

	if ((n = ft_strlen(s)) == 0)
		n = 1;
	if (pt->precision == 0)
		return (ft_print_sp(pt->width, 32));
	if (pt->minus != 1)
	{
		if (pt->zero != 1 || (pt->zero == 1 && pt->precision != -1))
			ft_print_sp(pt->width - n, 32);
		else
			ft_print_sp(pt->width - n, 48);
	}
	write(1, s, n);
	if (pt->minus == 1)
		ft_print_sp(pt->width - n, 32);
	return (1);
}

int			ft_printf_u(t_form *pt)
{
	unsigned long int	lu;
	unsigned long int	lu2;
	char				*s;
	int					i;

	ft_length_u(pt, &lu);
	lu2 = lu;
	i = ft_count_num(lu2);
	s = ft_strnew(lu == 0 ? 1 : i);
	if (lu == 0)
		s[0] = '0';
	lu2 = lu;
	while (lu > 0)
	{
		s[--i] = lu % 10 + '0';
		lu /= 10;
	}
	ft_check_prec(pt, &s, 'l');
	ft_print_str(pt, s);
	free(s);
	return (1);
}
