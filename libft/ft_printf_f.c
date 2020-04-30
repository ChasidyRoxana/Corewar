/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 12:55:24 by croxana           #+#    #+#             */
/*   Updated: 2019/10/14 13:46:34 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long double	ft_pow10(long double d, int n)
{
	while (n-- > 0)
		d *= 10;
	return (d);
}

static void			ft_continue(t_form *pt, char *s, char *ds, long double d)
{
	int	n;

	n = ft_strlen(s) + ft_strlen(ds) + 1;
	n = n + (d < 0.0 || pt->plus == 1 || pt->space == 1 ? 1 : 0);
	if (pt->minus != 1 && pt->zero != 1)
		ft_print_sp(pt->width - n, 32);
	if (d < 0.0)
		write(1, "-", 1);
	else if (pt->plus == 1 || pt->space == 1)
		write(1, (pt->plus == 1 ? "+" : " "), 1);
	if (pt->minus != 1 && pt->zero == 1)
		ft_print_sp(pt->width - n, 48);
	ft_printf("%s.%s", s, ds);
	if (pt->minus == 1)
		ft_print_sp(pt->width - n, 32);
}

static int			ft_print_str(t_form *pt, char *s, char *ds, long double d)
{
	int	n;

	n = ft_strlen(s);
	n = n + (d < 0.0 || pt->plus == 1 || pt->space == 1 ? 1 : 0);
	if (pt->precision == 0)
	{
		n = n + (pt->hash == 1 ? 1 : 0);
		if (pt->minus != 1 && pt->zero != 1)
			ft_print_sp(pt->width - n, 32);
		if (d < 0.0)
			write(1, "-", 1);
		else if (pt->plus == 1 || pt->space == 1)
			write(1, (pt->plus == 1 ? "+" : " "), 1);
		if (pt->minus != 1 && pt->zero == 1)
			ft_print_sp(pt->width - n, 48);
		ft_printf("%s", s);
		if (pt->hash == 1)
			write(1, ".", 1);
		if (pt->minus == 1)
			ft_print_sp(pt->width - n, 32);
	}
	else
		ft_continue(pt, s, ds, d);
	return (1);
}

static char			*ft_check_ds(t_form *pt, long double d2)
{
	char	*ds;
	char	*tmp;
	int		i;

	ds = ft_itoa_l(ft_pow10(d2, pt->precision) + 0.5);
	if ((ft_pow10(d2, pt->precision) + 0.5) > ft_pow10(1, pt->precision))
	{
		ds[0] = '0';
		ds[6] = '\0';
	}
	i = 1;
	while ((int)ft_strlen(ds) < pt->precision && ft_pow10(d2, i) < 1.0)
	{
		tmp = ft_strjoin("0", ds);
		free(ds);
		ds = tmp;
		i++;
	}
	if ((int)ft_strlen(ds) < pt->precision)
		ft_check_prec(pt, &ds, 'r');
	return (ds);
}

int					ft_printf_f(t_form *pt)
{
	long double	d;
	long double	d2;
	char		*s;
	char		*ds;

	if (pt->llarge == 1 || pt->l == 1)
		d = va_arg(*(pt->ptr), long double);
	else
		d = (long double)va_arg(*(pt->ptr), double);
	if (d >= 0.0)
		d2 = d - (long)d;
	else
		d2 = -d + (long)d;
	if (pt->precision == -1)
		pt->precision = 6;
	if (pt->precision == 0)
		s = ft_itoa_l((long)((d < 0.0 ? -d : d) + 0.5));
	else
		s = ft_itoa_l((long)(d < 0.0 ? -d : d) + (long)(ft_pow10(d2,
		pt->precision) + 0.5) / (long)ft_pow10(1, pt->precision));
	ds = ft_check_ds(pt, d2);
	ft_print_str(pt, s, ds, d);
	free(s);
	free(ds);
	return (1);
}
