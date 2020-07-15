/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:33:38 by croxana           #+#    #+#             */
/*   Updated: 2019/10/14 13:46:25 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf_c(t_form *pt)
{
	int c;

	c = va_arg(*(pt->ptr), int);
	if (pt->minus != 1)
		ft_print_sp(pt, pt->width - 1, ' ');
	write(1, &c, 1);
	if (pt->minus == 1)
		ft_print_sp(pt, pt->width - 1, ' ');
	return (1);
}
