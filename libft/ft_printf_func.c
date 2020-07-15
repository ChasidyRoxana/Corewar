/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxana <croxana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 15:36:44 by croxana           #+#    #+#             */
/*   Updated: 2019/10/14 13:46:42 by croxana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_check_prec(t_form *pt, char **s, char side)
{
	int		n;
	char	*tmp;

	n = ft_strlen(*s);
	while (n++ < pt->precision)
	{
		if (side == 'l')
			tmp = ft_strjoin("0", *s);
		else
			tmp = ft_strjoin(*s, "0");
		free(*s);
		*s = tmp;
	}
}

int		ft_print_sp(t_form *pt, int n, char c)
{
	while (n-- > 0)
		write(pt->fd, &c, 1);
	return (1);
}

void	ft_length_u(t_form *pt, unsigned long int *li)
{
	if (pt->hh == 1)
		*li = (unsigned long)(unsigned char)va_arg(*(pt->ptr), unsigned int);
	else if (pt->h == 1)
		*li = (unsigned long)(unsigned short int)va_arg(*(pt->ptr),
		unsigned int);
	else if (pt->ll == 1 || pt->l == 1)
		*li = va_arg(*(pt->ptr), unsigned long);
	else
		*li = (unsigned long)va_arg(*(pt->ptr), unsigned int);
}
