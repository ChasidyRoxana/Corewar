/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarpukova <tkarpukova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 20:48:59 by tkarpukova        #+#    #+#             */
/*   Updated: 2020/07/07 21:14:03 by tkarpukova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>

int     main(void)
{  
    initscr();			/* Start curses mode 		  */
	printw("Hello World !!!");	/* Print Hello World		  */
	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */
    
    return (0);
}