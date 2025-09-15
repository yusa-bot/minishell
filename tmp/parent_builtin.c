/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:24:47 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/08 22:19:02 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//子プロセスを作ると環境変数やカレントディレクトリの変更が親に反映されないので、親プロセスで実行する必要があります。
//ビルトインの結果をファイルに出力したい場合、親プロセスの標準入出力を一時的に変更し、実行後に元に戻す必要があるためです

//dup_restore()のため
static int	dup_save(int *save_stdin, int *save_stdout)
{
	// 標準入力・標準出力を複製して保存
	*save_stdin = dup(STDIN_FILENO);
	*save_stdout = dup(STDOUT_FILENO);
	if (*save_stdin < 0 || *save_stdout < 0)
		return (-1);
	return (0);
}

// 保存した標準入出力を元に戻す
static void	dup_restore(int save_stdin, int save_stdout)
{
	// 標準入力を元に戻す
	if (save_stdin >= 0)
	{
		dup2(save_stdin, STDIN_FILENO);
		close(save_stdin);
	}
	// 標準出力を元に戻す
	if (save_stdout >= 0)
	{
		dup2(save_stdout, STDOUT_FILENO);
		close(save_stdout);
	}
}

// リダイレクト付きのビルトインコマンドを親プロセスで安全に実行
int	run_single_builtin_in_parent(t_cmd *c, t_env **env)
{
	int	save_in;
	int	save_out;
	int	status;

	save_in = -1;
	save_out = -1;
	// 現在の標準入出力を保存
	if (dup_save(&save_in, &save_out) < 0)
	{
		perror("dup");
		return (1);
	}
	// リダイレクトを適用
	if (apply_redirections(c) < 0)
	{
		dup_restore(save_in, save_out);
		return (1);
	}
	// ビルトインコマンドを実行
	status = run_builtin(c->cmd_args[0], c->cmd_args, env);
	// 標準入出力を元に戻す
	dup_restore(save_in, save_out);
	return (status);
}
