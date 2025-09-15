/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:45:06 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/15 18:21:42 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 判定と実行
int is_builtin(char **args, t_env **env)
{
    if (!args || !args[0])
        return (0);
    if (!ft_strcmp(args[0], "echo"))
        return (ft_echo(args, env), 1);
    else if (!ft_strcmp(args[0], "pwd"))
        return (ft_pwd(env), 1);
    else if (!ft_strcmp(args[0], "env"))
        return (ft_env(env), 1);//fd
    else if (!ft_strcmp(args[0], "cd"))
        return (ft_cd(args, env), 1);
    else if (!ft_strcmp(args[0], "export"))
        return (ft_export(args, env), 1);//fd
    else if (!ft_strcmp(args[0], "unset"))
        return (ft_unset(env, args[1]), 1);//引数あってる？
    else if (!ft_strcmp(args[0], "exit"))
        return (ft_exit(args), 1);
    return (0);
}

int run_child(t_cmd *cmd, t_env **env)
{
    pid_t pid;
    int   status;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return (1);
    }
    if (pid == 0)
    {
        // pipeでも使い回しているため、全てのbuildinかを判定している。
            //単独の場合、そもそもこの関数は通らない。
        if (!is_builtin(cmd->cmd_args[0], env))//builtin
        {   //external
            char *path = search_path(cmd->cmd_args[0], *env);
            if (!path)
            {
                fprintf(stderr, "%s: command not found\n", cmd->cmd_args[0]);
                exit(127);
            }
            execve(path, cmd->cmd_args, env_to_array(*env));
            perror("execve");
            exit(126);
        }
    }
    else//親(終了コード管理)
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
        if (WIFSIGNALED(status))
            return (128 + WTERMSIG(status));
    }
    return (1);
}

//1. waitpid(pid, &status, 0)
//&status: 子プロセスの終了状態
//0: 子プロセスが終了するまで親プロセスを停止

//2. WIFEXITED(status): 子プロセスが正常終了したか
//3. WEXITSTATUS(status): 正常終了した子プロセスの終了コード
//例: 子プロセスがexit(42)で終了 → WEXITSTATUS(status)は42


//4. WIFSIGNALED(status): 子プロセスがシグナルで終了したかをチェック
//SIGKILL、SIGTERM、SIGSEGVなどで強制終了

//5. WTERMSIG(status): 子プロセスを終了させたシグナル番号を取得


//6. 128 + WTERMSIG(status)
//シェルの慣例: シグナル終了時の終了コード
//計算: 128 + シグナル番号

