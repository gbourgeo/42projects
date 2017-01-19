/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/06 16:54:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 07:47:37 by gsaynac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

int		ft_check_double_pipe(char **args, int i);
int		ft_check_semi_colon(char **args, int i);
int		ft_check_double_and(char **args, int i);
int		ft_check_redirect_left(char **args, int i);
int		ft_check_redirect_right(char **args, int i);
int		ft_check_redirect_pipe(char **args, int i);

#endif
