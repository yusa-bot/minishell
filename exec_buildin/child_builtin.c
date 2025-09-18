/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:45:06 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/18 21:35:49 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_cmd *cmd, t_env **env, t_shell *shell)
{
	setup_signals_child();
	apply_redirect(cmd);
	if (is_builtin_child(cmd->cmd_args))
	{
		shell->status = run_builtin(&cmd->cmd_args[0], env, shell);
		exit(shell->status);
	}
	else //external
	{
		char *path = search_external_path(cmd->cmd_args[0], env);
		execve(path, cmd->cmd_args, env_to_array(*env));
		perror("execve");
		exit(EXIT_NO_EXEC);
	}
}

int run_child(t_cmd *cmd, t_env **env, t_shell *shell)
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
