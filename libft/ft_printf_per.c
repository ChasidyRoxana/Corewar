/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_per.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:01:35 by croxana           #+#    #+#             */
/*   Updated: 2019/10/14 13:46:49 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf_per(t_form *pt)
{
	if (pt->minus != 1)
	{
		if (pt->zero == 1)
			ft_print_sp(pt, pt->width - 1, '0');
		else
			ft_print_sp(pt, pt->width - 1, ' ');
	}
	write(1, "%%", 1);
	if (pt->minus == 1)
		ft_print_sp(pt, pt->width - 1, ' ');
	return (1);
}
