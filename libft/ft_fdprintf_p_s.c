/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf_p_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:28:41 by marvin            #+#    #+#             */
/*   Updated: 2020/07/15 18:28:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_p(t_form *pt, char *s)
{
	int n;

	n = ft_strlen(s);
	if (n == 0)
		n = 1;
	if (pt->minus != 1)
		ft_print_sp(pt, pt->width - n - 2, ' ');
	write(pt->fd, "0x", 2);
	if (pt->precision != 0)
		write(pt->fd, s, ft_strlen(s));
	if (pt->minus == 1)
		ft_print_sp(pt, pt->width - n - 2, ' ');
	return (1);
}

int			ft_fdprintf_p(t_form *pt)
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

static int	ft_print_str(t_form *pt, char *s, int len)
{
	if (pt->minus != 1)
		ft_print_sp(pt, pt->width - len, (pt->zero == 1 ? '0' : ' '));
	write(pt->fd, s, len);
	if (pt->minus == 1)
		ft_print_sp(pt, pt->width - len, ' ');
	return (1);
}

int			ft_fdprintf_s(t_form *pt)
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
