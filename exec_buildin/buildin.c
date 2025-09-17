/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:23:08 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/17 23:24:31 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin_parent(char **args)
{
    if (!args || !args[0])
        return (0);
    return (!ft_strcmp(args[0], "cd")
         || !ft_strcmp(args[0], "export")
         || !ft_strcmp(args[0], "unset")
         || !ft_strcmp(args[0], "exit"));
}

int is_builtin_child(char **args)
{
	if (!args || !args[0])
		return (0);
	return (!ft_strcmp(args[0], "echo")
		 || !ft_strcmp(args[0], "pwd")
		 || !ft_strcmp(args[0], "env"));
}

// 判定と実行 共通
int run_builtin(char **args, t_env **env, t_shell *shell)//TODO 各関数にshellを渡す
{
    if (!args || !args[0])
        return (0);
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args, env), 1);
	else if (!ft_strcmp(args[0], "export"))
		return (ft_export(*env, STDOUT_FILENO), 1);
	else if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(env, args[1]), 1);
	else if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args), 1);
これらが親プロセス・子プロセスのときのstatusの戻り方を実装する。

子だったらexit、親だったら
でそこまで戻せば良い。

    else if (!ft_strcmp(args[0], "echo"))
        ft_echo(args, STDOUT_FILENO, shell);
    else if (!ft_strcmp(args[0], "pwd"))
        ft_pwd(*env, STDOUT_FILENO, shell);
    else if (!ft_strcmp(args[0], "env"))
        ft_env(*env, STDOUT_FILENO, shell);

    return (0);
}
