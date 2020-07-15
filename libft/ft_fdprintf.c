/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:46:23 by marvin            #+#    #+#             */
/*   Updated: 2020/07/15 17:46:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_type(t_form *pt)
{
	if (pt->format[pt->i] == 'c')
		ft_fdprintf_c(pt);
	else if (pt->format[pt->i] == 's')
		ft_fdprintf_s(pt);
	else if (pt->format[pt->i] == 'p')
		ft_fdprintf_p(pt);
	else if (pt->format[pt->i] == '%')
		ft_fdprintf_per(pt);
	else if (pt->format[pt->i] == 'x' || pt->format[pt->i] == 'X')
		ft_fdprintf_x(pt);
	else if (pt->format[pt->i] == 'o')
		ft_fdprintf_o(pt);
	else if (pt->format[pt->i] == 'u' || pt->format[pt->i] == 'D')
		ft_fdprintf_u(pt);
	else if (pt->format[pt->i] == 'd' || pt->format[pt->i] == 'i')
		ft_fdprintf_di(pt);
	else if (pt->format[pt->i] == 'f' || pt->format[pt->i] == 'F')
		ft_fdprintf_f(pt);
	else if (pt->format[pt->i] == 'b')
		ft_fdprintf_b(pt);
	return (1);
}

static int	ft_type_check(t_form *pt)
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

static void	ft_form_fill(t_form *pt)
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

static int	ft_flags(t_form *pt)
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
		else
			write(pt->fd, &(pt->format[pt->i]), 1);
		pt->i++;
		pt->j++;
	}
	return (1);
}

int			ft_fdprintf(int fd, const char *restrict format, ...)
{
	va_list	ptr;
	t_form	pt;

	va_start(ptr, format);
	pt.format = ft_strdup(format);
	pt.ptr = &ptr;
	pt.fd = fd;
	ft_flags(&pt);
	va_end(ptr);
	free(pt.format);
	return (1);
}
