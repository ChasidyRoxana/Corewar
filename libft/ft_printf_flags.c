/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:08:54 by croxana           #+#    #+#             */
/*   Updated: 2019/10/14 14:03:39 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_flag_one(t_form *pt)
{
	while (pt->format[pt->j] == '0' || pt->format[pt->j] == '+' ||
		pt->format[pt->j] == '-' || pt->format[pt->j] == ' ' ||
		pt->format[pt->j] == '#')
	{
		if (pt->format[pt->j] == '0')
			pt->zero = 1;
		else if (pt->format[pt->j] == '+')
			pt->plus = 1;
		else if (pt->format[pt->j] == '-')
			pt->minus = 1;
		else if (pt->format[pt->j] == ' ')
			pt->space = 1;
		else if (pt->format[pt->j] == '#')
			pt->hash = 1;
		pt->j++;
	}
	return (1);
}

static void	ft_j_plus(t_form *pt)
{
	while ((pt->format[pt->j] >= '0' && pt->format[pt->j] <= '9') ||
		pt->format[pt->j] == '*')
		pt->j++;
}

int			ft_flag_two(t_form *pt)
{
	if (pt->format[pt->j] >= '0' && pt->format[pt->j] <= '9')
		pt->width = ft_atoi(&(pt->format[pt->j]));
	if (pt->format[pt->j] == '*')
		pt->width = va_arg(*(pt->ptr), int);
	ft_j_plus(pt);
	if (pt->format[pt->j] == '.')
	{
		pt->j++;
		pt->precision = (pt->format[pt->j] >= '0' && pt->format[pt->j] <= '9') ?
			ft_atoi(&(pt->format[pt->j])) : 0;
	}
	if (pt->format[pt->j] == '*')
		pt->precision = va_arg(*(pt->ptr), int);
	ft_j_plus(pt);
	if (pt->width < 0)
	{
		pt->minus = 1;
		pt->width = -(pt->width);
	}
	return (1);
}

int			ft_flag_three(t_form *pt)
{
	while (pt->format[pt->j] == 'l' || pt->format[pt->j] == 'h' ||
		pt->format[pt->j] == 'L')
	{
		if (pt->format[pt->j] == 'L')
			pt->llarge = 1;
		else if (pt->format[pt->j] == pt->format[pt->j + 1])
		{
			if (pt->format[pt->j] == 'l')
				pt->ll = 1;
			else
				pt->hh = 1;
			pt->j++;
		}
		else if (pt->format[pt->j] == 'l')
			pt->l = 1;
		else if (pt->format[pt->j] == 'h')
			pt->h = 1;
		pt->j++;
	}
	return (1);
}
