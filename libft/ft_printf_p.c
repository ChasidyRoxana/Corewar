/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:17:25 by croxana           #+#    #+#             */
/*   Updated: 2019/10/14 13:46:46 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_count_b(unsigned long int n, int c)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n >>= c;
		i++;
	}
	return (i);
}

static int	ft_print_p(t_form *pt, char *s)
{
	int n;

	n = ft_strlen(s);
	if (n == 0)
		n = 1;
	if (pt->minus != 1)
		ft_print_sp(pt->width - n - 2, ' ');
	ft_printf("0x");
	if (pt->precision != 0)
		ft_printf("%s", s);
	if (pt->minus == 1)
		ft_print_sp(pt->width - n - 2, ' ');
	return (1);
}

int			ft_printf_p(t_form *pt)
{
	unsigned long int	num;
	unsigned long int	n;
	char				*s;
	int					i;

	num = (unsigned long int)va_arg(*(pt->ptr), void*);
	i = ft_count_b(num, 4);
	s = ft_strnew(num == 0 ? 1 : i);
	if (num == 0)
		s[0] = '0';
	while (num > 0)
	{
		n = num % 16;
		s[--i] = (n > 9) ? n + 'W' : n + '0';
		num >>= 4;
	}
	ft_check_prec(pt, &s, 'l');
	ft_print_p(pt, s);
	free(s);
	return (1);
}
