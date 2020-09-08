/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Screen.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 16:14:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/03 16:15:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_HPP
 #define SCREEN_HPP

# include <curses.h>

class Screen
{
public:

	Screen(int height, int width);
	~Screen(void);
	Screen(Screen const &ref);
	
	Screen & operator=(Screen const &ref);

	void		setHeight(int height);
	void		setWidth(int width);
	void		setWindow(WINDOW *w);

	int			getHeight(void) const;
	int			getWidth(void) const;
	WINDOW		*getWindow(void) const;
	int			transformX(int x);
	int			transformY(int y);

private:

	Screen(void);
	WINDOW      *window;

	// Current Max Window Height
	int         height;

	// Current Max Window Width
	int         width;
};

#endif