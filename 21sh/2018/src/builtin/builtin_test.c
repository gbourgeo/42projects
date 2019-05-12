/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:16:17 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/26 01:06:44 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"
#include "shell_lib.h"

int		builtin_test(t_execute *exec, t_s_env *e)
{
	int		size;

	(void)e;
	size = sh_tablen((const char **)exec->cmd);
	if (size == 1)
		return (1);
	if (size == 2)
		return ((exec->cmd[1][0] != '\0') ? 0 : 1);
	if (size >= 5)
		return (test_four_arg(exec->cmd, size));
	if (size == 3)
	{
		if (ft_strcmp(exec->cmd[1], "!") == 0)
			return (exec->cmd[2][0] == '\0' ? 0 : 1);
		return (test_two_arg(exec->cmd[1], exec->cmd[2]));
	}
	if (size == 4)
		return (test_three_arg(exec->cmd[1], exec->cmd[2], exec->cmd[3]));
	return (0);
}

int		test_two_arg(char *arg1, char *arg2)
{
	(void)arg2;
	if (arg1[0] != '-' || ft_strlen(arg1) != 2)
	{
		ft_dprintf(2, "42sh: test: %s: unary operator expected\n", arg1);
		return (2);
	}
	else
		return (test_two_arg_exec(arg1, arg2));
}

int		test_two_arg_exec(char *arg1, char *arg2)
{
	static t_operators	operators[] = {
	OPERATOR_B, OPERATOR_C, OPERATOR_D, OPERATOR_E, OPERATOR_F, OPERATOR_G,
	OPERATOR_LL, OPERATOR_P, OPERATOR_R, OPERATOR_SS, OPERATOR_S, OPERATOR_U,
	OPERATOR_W, OPERATOR_X, OPERATOR_Z,
	};
	size_t				i;

	i = 0;
	while (i < sizeof(operators) / sizeof(operators[0]))
	{
		if (!ft_strcmp(operators[i].name, arg1))
			return (operators[i].handler(arg2));
		i++;
	}
	ft_dprintf(2, "42sh: test: %s: unary operator expected\n", arg1);
	return (2);
}

int		test_three_arg(char *arg1, char *arg2, char *arg3)
{
	static t_binary_ops		binary_ops[] = {
	BINARY_OP_EQ_ST, BINARY_OP_NE_ST, BINARY_OP_EQ_INT,
	BINARY_OP_NE_INT, BINARY_OP_GE_INT, BINARY_OP_LT_INT,
	BINARY_OP_LE_INT, BINARY_OP_GT_INT,
	};
	size_t					i;
	int						ret;

	i = 0;
	if (ft_strcmp(arg1, "!") == 0)
	{
		ret = test_two_arg(arg2, arg3);
		if (ret == 2)
			return (2);
		return ((ret == 1) ? 0 : 1);
	}
	while (i < sizeof(binary_ops) / sizeof(binary_ops[0]))
	{
		if (!ft_strcmp(binary_ops[i].name, arg2))
			return (binary_ops[i].handler(arg1, arg3));
		i++;
	}
	ft_dprintf(2, "42sh: test: %s: binary operator expected\n", arg2);
	return (2);
}

int		test_four_arg(char **cmd, int size)
{
	int ret;

	if (size == 5 && ft_strcmp(cmd[1], "!") == 0)
	{
		ret = test_three_arg(cmd[2], cmd[3], cmd[4]);
		if (ret == 1)
			return (0);
		if (ret == 0)
			return (1);
		return (ret);
	}
	ft_dprintf(2, "42sh: test: too many arguments\n");
	return (2);
}
