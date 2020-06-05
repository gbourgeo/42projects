/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Screen.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 16:16:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/03 16:16:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Screen.hpp"
#include "main.hpp"

Screen::Screen(int height, int width): height(height), width(width) {
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	this->window = newwin(HEIGHT,WIDTH,0,0);
	keypad(this->window, true);
	nodelay(this->window, true);
}

Screen::~Screen(void) {
	endwin();
}

Screen::Screen(Screen const &ref) {
	*this = ref;
}

Screen & Screen::operator=(Screen const & rhs) {
	if (this != &rhs)
	{
		this->window = rhs.getWindow();
		this->height = rhs.getHeight();
		this->width = rhs.getWidth();
	}
	return *this;
}

int            Screen::getHeight(void) const {
    return this->height;
}

int            Screen::getWidth(void) const {
    return this->width;
}

WINDOW            *Screen::getWindow(void) const {
    return this->window;
}

void           Screen::setHeight(int height) {
    this->height = height;
}

void           Screen::setWidth(int width) {
    this->width = width;
}

void           Screen::setWindow(WINDOW *w) {
    this->window = w;
}

int             Screen::transformX(int x) {
    return (int)((float)(x / WIDTH) * this->getWidth());
}

int             Screen::transformY(int y) {
    return this->getHeight() - (int)((float)(y / HEIGHT) * this->getHeight());
}
