/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:45:06 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/28 10:39:45 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_external(t_shell *sh)
{
	fprintf(stderr, "exec_external\n");
	char	*msg;
	struct stat st;

	char *path = search_external_path(sh->cmd->cmd_args[0], &sh->env);
	if (!path)
	{
		msg = ft_strjoin_oneptr("minishell: ", sh->cmd->cmd_args[0]);
		msg = ft_strjoin_oneptr(msg, ": command not found\n");
		ft_putendl_fd(msg, 2);
		free(msg);
		return (127); //free(msg);
	}

	char **envp = env_to_array(sh->env);
	execve(path, sh->cmd->cmd_args, envp);

	// execve失敗後の処理 各msgを出してstatusでreturn -> 呼び出し元でclean up & exit & sh->statusに保存
	if (envp)
		free_split(envp);

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		free(path);
		msg = ft_strjoin_oneptr("minishell: ", sh->cmd->cmd_args[0]);
		msg = ft_strjoin_oneptr(msg, ": Is a directory\n");
		ft_putendl_fd(msg, 2);
		free(msg);
		return (126); //free(msg);
	}
	free(path);

	msg = ft_strjoin("minishell: ", sh->cmd->cmd_args[0]);
	perror(msg);
	free(msg);

	if (errno == EACCES || errno == EISDIR)
		return (126); // Permission denied / Is a directory
	else if (errno == ENOENT)
		return (127); // command not found
	else
		return (126); // その他
}

int	exec_child(t_shell *sh)
{
	fprintf(stderr, "exec_child\n");
	setup_signals_child();

	if (sh->cmd->infile || sh->cmd->outfile)
		sh->status = apply_redirect(sh);

	if (is_builtin_parent(sh->cmd->cmd_args) || is_builtin_child(sh->cmd->cmd_args))
		return (run_builtin(sh, &sh->cmd->cmd_args[0])); //必ず戻ってくる
	else //external
		sh->status = exec_external(sh);
	return (sh->status);
}

int exec_child_handler(t_shell *sh)
{
	fprintf(stderr, "exec_child_handler\n");
    pid_t pid;

    pid = fork();
	if (pid < 0)
		perror_exit("fork");

    if (pid == 0)
	{
		sh->status = exec_child(sh);
		exit(sh->status); //後処理は親
	}

    else//単独コマンドだったらこっちが親
    {
        waitpid(pid, &sh->status, 0); // sh->statusに子プロセスの終了コードを保存
        if (WIFEXITED(sh->status))
            return (WEXITSTATUS(sh->status));
        if (WIFSIGNALED(sh->status))
            return (128 + WTERMSIG(sh->status));
    }
	return (sh->status);
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
