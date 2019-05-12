/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:22:38 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/29 01:49:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_TEST_H
# define BUILTIN_TEST_H
# ifdef __linux
#  define S_IREAD	S_IRUSR
#  define S_IWRITE	S_IWUSR
#  define S_IEXEC	S_IXUSR
# endif
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include "ft_printf.h"
# include "ft_dprintf.h"

# define OPERATOR_B			{ "-b"	, operator_b }
# define OPERATOR_C			{ "-c"	, operator_c }
# define OPERATOR_D			{ "-d"	, operator_d }
# define OPERATOR_E			{ "-e"	, operator_e }
# define OPERATOR_F			{ "-f"	, operator_f }
# define OPERATOR_G			{ "-g"	, operator_g }
# define OPERATOR_LL		{ "-L"	, operator_ll }
# define OPERATOR_P			{ "-p"	, operator_p }
# define OPERATOR_R			{ "-r"	, operator_r }
# define OPERATOR_SS		{ "-S"	, operator_ss }
# define OPERATOR_S			{ "-s"	, operator_s }
# define OPERATOR_U			{ "-u"	, operator_u }
# define OPERATOR_W			{ "-w"	, operator_w }
# define OPERATOR_X			{ "-x"	, operator_x }
# define OPERATOR_Z			{ "-z"	, operator_z }
# define BINARY_OP_EQ_ST	{ "="	, operator_eq_st }
# define BINARY_OP_NE_ST	{ "!="	, operator_ne_st }
# define BINARY_OP_EQ_INT	{ "-eq"	, operator_eq_int }
# define BINARY_OP_NE_INT	{ "-ne"	, operator_ne_int }
# define BINARY_OP_GE_INT	{ "-ge"	, operator_ge_int }
# define BINARY_OP_LT_INT	{ "-lt"	, operator_lt_int }
# define BINARY_OP_LE_INT	{ "-le"	, operator_le_int }
# define BINARY_OP_GT_INT	{ "-gt"	, operator_gt_int }

typedef struct	s_operators
{
	char		*name;
	int			(*handler)(char *);
}				t_operators;

typedef struct	s_binary_ops
{
	char		*name;
	int			(*handler)(char *, char *);
}				t_binary_ops;

int				test_two_arg(char *arg1, char *arg2);
int				test_two_arg_exec(char *arg1, char *arg2);
int				test_three_arg(char *arg1, char *arg2, char *arg3);
int				test_four_arg(char **cmd, int size);
int				operator_b(char *arg);
int				operator_c(char *arg);
int				operator_d(char *arg);
int				operator_e(char *arg);
int				operator_f(char *arg);
int				operator_g(char *arg);
int				operator_ll(char *arg);
int				operator_p(char *arg);
int				operator_r(char *arg);
int				operator_ss(char *arg);
int				operator_s(char *arg);
int				operator_u(char *arg);
int				operator_w(char *arg);
int				operator_x(char *arg);
int				operator_z(char *arg);
int				ft_isnumber(char *s);
int				operator_eq_st(char *arg1, char *arg3);
int				operator_ne_st(char *arg1, char *arg3);
int				operator_eq_int(char *arg1, char *arg3);
int				operator_ne_int(char *arg1, char *arg3);
int				operator_ge_int(char *arg1, char *arg3);
int				operator_lt_int(char *arg1, char *arg3);
int				operator_le_int(char *arg1, char *arg3);
int				operator_gt_int(char *arg1, char *arg3);

#endif
