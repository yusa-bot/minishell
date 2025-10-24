/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:45:06 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/24 13:34:00 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_child(t_shell *sh)
{
	setup_signals_child();
	sh->status = apply_redirect(sh);
	if (sh->status != EXIT_SUCCESS)////
        return sh->status;
	printf("exec_child called: %s\n", sh->cmd->cmd_args[0]);
	if (is_builtin_child(sh->cmd->cmd_args))
		return (run_builtin(sh, &sh->cmd->cmd_args[0]));
	else //external
	{
		printf("exec_child external: %s\n", sh->cmd->cmd_args[0]);
		char *path = search_external_path(sh->cmd->cmd_args[0], sh->env);
		if (!path)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, sh->cmd->cmd_args[0], ft_strlen(sh->cmd->cmd_args[0]));
			write(STDERR_FILENO, ": command not found\n", 20);
			return (127);
		}
		char **envp = env_to_array(sh->env);
		execve(path, sh->cmd->cmd_args, envp);
		free(path);
		if (envp)
			free_split(envp);

		struct stat st;
		if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, sh->cmd->cmd_args[0], ft_strlen(sh->cmd->cmd_args[0]));
			write(STDERR_FILENO, ": Is a directory\n", 17);
			return (126);
		}

		char *msg = ft_strjoin("minishell: ", sh->cmd->cmd_args[0]);
		if (!msg)
		{
			perror("malloc");
			exit(EXIT_FAILURE);//?
		}
		perror(msg);
		free(msg);

		if (errno == EACCES || errno == EISDIR)
			return (126); // Permission denied / Is a directory
		else if (errno == ENOENT)
			return (127); // command not found
		else
			return (126); // その他
	}
}

int run_child(t_shell *sh)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
		perror("fork");
		exit(EXIT_FAILURE);
    }
    if (pid == 0)
	{
		sh->status = exec_child(sh);
		if (sh->status != EXIT_SUCCESS)
			exit(sh->status);
	}
    else//単独コマンドだったらこっちが親
    {
        waitpid(pid, &sh->status, 0);
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
