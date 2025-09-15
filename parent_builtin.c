/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:24:47 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/15 16:11:25 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 現在の標準入出力を保存
// リダイレクトを適用
// ビルトインコマンドを実行
// 標準入出力を元に戻す

// 判定と実行
int run_parent(char **args, t_env **env)
{
    if (!args || !args[0])
        return (0);
    if (!ft_strcmp(args[0], "cd"))
        return (ft_cd(args, env), 1);
    else if (!ft_strcmp(args[0], "export"))
        return (ft_export(args, env), 1);//fd
    else if (!ft_strcmp(args[0], "unset"))
        return (ft_unset(env, args[1]), 1);//引数あってる？
    else if (!ft_strcmp(args[0], "exit"))
        return (ft_exit(args), 1);

    return (0);
}
