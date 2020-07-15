/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:28:23 by croxana           #+#    #+#             */
/*   Updated: 2019/10/14 13:46:51 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_str(t_form *pt, char *s, int len)
{
	if (pt->minus != 1)
		ft_print_sp(pt, pt->width - len, (pt->zero == 1 ? '0' : ' '));
	write(1, s, len);
	if (pt->minus == 1)
		ft_print_sp(pt, pt->width - len, ' ');
	return (1);
}

int			ft_printf_s(t_form *pt)
{
	char	*s;
	int		len;

	s = va_arg(*(pt->ptr), char*);
	if (s == 0)
		s = "(null)";
	len = ft_strlen(s);
	if (pt->precision != -1 && len > pt->precision)
		ft_print_str(pt, s, pt->precision);
	else
		ft_print_str(pt, s, len);
	return (1);
}
