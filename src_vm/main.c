/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 12:28:20 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/05 12:47:05 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		main(int argc, char **argv)
{
	argv[0] = NULL;
	if (argc < 2)
		return (1);
	return (0);
}