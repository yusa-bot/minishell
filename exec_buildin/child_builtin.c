/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:45:06 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/17 00:22:43 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_child(t_cmd *cmd, t_env **env, t_shell shell)
{
	setup_signals_child();
	if (apply_redirect(cmd) < 0)//
		exit(1);

	if (!run_builtin(&cmd->cmd_args[0], env, shell))//builtin//
	{   //external
		char *path = search_external_path(cmd->cmd_args[0], env);//
		if (!path)
		{
			write(2, cmd->cmd_args[0], strlen(cmd->cmd_args[0]));
			write(2, ": command not found\n", 20);
			exit(127);
		}
		execve(path, cmd->cmd_args, env_to_array(*env));
		perror("execve");
		exit(126);
	}
}
ここのエラー処理から。

int run_child(t_cmd *cmd, t_env **env, t_shell shell)
{
    pid_t pid;
    int   status;

    pid = fork();
    if (pid < 0)
    {
		perror("pipe");
		exit(EXIT_FAILURE);
    }
    if (pid == 0)
		exec_child(cmd, env, shell);
	//単独コマンドだったらこっちが親
    else
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
