/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:40:54 by croxana           #+#    #+#             */
/*   Updated: 2019/12/12 12:44:48 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_print_type(t_form *pt)
{
	if (pt->format[pt->i] == 'c')
		ft_printf_c(pt);
	else if (pt->format[pt->i] == 's')
		ft_printf_s(pt);
	else if (pt->format[pt->i] == 'p')
		ft_printf_p(pt);
	else if (pt->format[pt->i] == '%')
		ft_printf_per(pt);
	else if (pt->format[pt->i] == 'x' || pt->format[pt->i] == 'X')
		ft_printf_x(pt);
	else if (pt->format[pt->i] == 'o')
		ft_printf_o(pt);
	else if (pt->format[pt->i] == 'u' || pt->format[pt->i] == 'D')
		ft_printf_u(pt);
	else if (pt->format[pt->i] == 'd' || pt->format[pt->i] == 'i')
		ft_printf_di(pt);
	else if (pt->format[pt->i] == 'f' || pt->format[pt->i] == 'F')
		ft_printf_f(pt);
	else if (pt->format[pt->i] == 'b')
		ft_printf_b(pt);
	return (1);
}

int		ft_type_check(t_form *pt)
{
	while (pt->format[pt->i] != '\0' && pt->format[pt->i] != 'c' &&
		pt->format[pt->i] != 's' && pt->format[pt->i] != 'p' &&
		pt->format[pt->i] != 'd' && pt->format[pt->i] != 'i' &&
		pt->format[pt->i] != 'f' && pt->format[pt->i] != 'o' &&
		pt->format[pt->i] != 'u' && pt->format[pt->i] != 'x' &&
		pt->format[pt->i] != 'X' && pt->format[pt->i] != '%' &&
		pt->format[pt->i] != 'D' && pt->format[pt->i] != 'F' &&
		pt->format[pt->i] != 'b')
		pt->i++;
	if (pt->format[pt->i] != pt->format[pt->j])
		ft_flag_one(pt);
	if (pt->format[pt->i] != pt->format[pt->j])
		ft_flag_two(pt);
	if (pt->format[pt->i] != pt->format[pt->j])
		ft_flag_three(pt);
	ft_print_type(pt);
	return (1);
}

void	ft_form_fill(t_form *pt)
{
	pt->width = 0;
	pt->precision = -1;
	pt->plus = 0;
	pt->minus = 0;
	pt->space = 0;
	pt->zero = 0;
	pt->hash = 0;
	pt->l = 0;
	pt->ll = 0;
	pt->h = 0;
	pt->hh = 0;
	pt->llarge = 0;
}

int		ft_flags(t_form *pt)
{
	pt->i = 0;
	pt->j = 0;
	while (pt->format[pt->i] != '\0')
	{
		if (pt->format[pt->i] == '%')
		{
			pt->i++;
			pt->j++;
			ft_form_fill(pt);
			ft_type_check(pt);
		}
		else if (pt->format[pt->i] == '{')
			ft_printf_color(pt);
		else
			write(1, &(pt->format[pt->i]), 1);
		pt->i++;
		pt->j++;
	}
	return (1);
}

int		ft_printf(const char *restrict format, ...)
{
	va_list	ptr;
	t_form	pt;

	va_start(ptr, format);
	pt.format = ft_strdup(format);
	pt.ptr = &ptr;
	ft_flags(&pt);
	va_end(ptr);
	free(pt.format);
	return (1);
}
