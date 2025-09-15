/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:23:08 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/15 22:07:07 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_parent(char **args)
{
    if (!args || !args[0])
        return (0);
    return (!ft_strcmp(args[0], "cd")
         || !ft_strcmp(args[0], "export")
         || !ft_strcmp(args[0], "unset")
         || !ft_strcmp(args[0], "exit"));
}

// 判定と実行 共通
int run_builtin(char **args, t_env **env, t_shell shell)
{
    if (!args || !args[0])
        return (0);
    if (!ft_strcmp(args[0], "echo"))
        return (ft_echo(args, STDOUT_FILENO, shell), 1);
    else if (!ft_strcmp(args[0], "pwd"))
        return (ft_pwd(*env, STDOUT_FILENO), 1);
    else if (!ft_strcmp(args[0], "env"))
        return (ft_env(*env, STDOUT_FILENO), 1);
    else if (!ft_strcmp(args[0], "cd"))
        return (ft_cd(args, env), 1);
    else if (!ft_strcmp(args[0], "export"))
        return (ft_export(*env, STDOUT_FILENO), 1);
    else if (!ft_strcmp(args[0], "unset"))
        return (ft_unset(env, args[1]), 1);
    else if (!ft_strcmp(args[0], "exit"))
        return (ft_exit(args), 1);
    return (0);
}
