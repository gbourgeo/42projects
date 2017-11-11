// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   stdlib_func.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 15:55:59 by root              #+#    #+#             //
//   Updated: 2017/11/05 20:58:02 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef STDLIB_FUNC_HPP
# define STDLIB_FUNC_HPP

const void *	mymemset(const void *s, int c, unsigned int n);
const char *	mystrcpy(const char *dst, const char *src);
const char *	mystrncpy(const char *dst, const char *src, int len);
const char *	mystrcat(const char *dst, const char *src);
size_t			mystrlen(const char *s);
char *			mystrchr(const char *s, char c);
int				mystrcmp(const char *s1, const char *s2);
int				myisalnum(char c);

#endif
