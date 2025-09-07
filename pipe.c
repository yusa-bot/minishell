/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 13:48:40 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/07 20:23:03 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pipeline.c：パイプ列の実行（ビルトイン混在OK）
// 各コマンドを子プロセスで実行する関数
static void child_exec(t_cmd *c, int in_fd, int out_fd, t_env **env)
{
    // 子プロセス用のシグナルハンドラを設定（SIG_DFL）
    setup_signals_child();
    // パイプからparent_builtin.cの入力を標準入力に接続
    if (in_fd != STDIN_FILENO)  { dup2(in_fd, STDIN_FILENO); close(in_fd); }
    // パイプへの出力を標準出力に接続
    if (out_fd != STDOUT_FILENO){ dup2(out_fd, STDOUT_FILENO); close(out_fd); }

    // リダイレクト適用（失敗時は子プロセス終了）
    if (apply_redirections(c) < 0)
        _exit(1);

    // ビルトインコマンドかつ親プロセス専用でない場合は子プロセスで実行
    if (is_builtin_name(c->cmd_args && c->cmd_args[0] ? c->cmd_args[0] : NULL)
        && !must_run_in_parent(c->cmd_args[0]))
    {
        int st = run_builtin(c->cmd_args[0], c->cmd_args, env);
        _exit(st);
    }
    // 外部コマンドの場合：実行可能ファイルのパスを解決してexecve
    char *exec_path = resolve_exec_path(c->cmd_args[0], *env);
    if (!exec_path) {
        // コマンドが見つからない場合
        _exit(127);
    }
    execve(exec_path, c->cmd_args, /* envp 文字列配列 */ build_envp_array(*env));
    perror("execve");
    _exit(126);
}

int execute_pipeline(t_cmd *head, t_env **env)
{
    // コマンド数をカウント
    int n = 0; for (t_cmd *p=head; p; p=p->next) n++;
    int pipes[2*(n-1)];  // パイプ配列（各パイプは[read_fd, write_fd]）
    pid_t pids[n];       // 子プロセスID配列
    int i = 0;

    // 必要な分だけパイプを作成
    for (int k=0; k<n-1; k++)
        if (pipe(pipes + 2*k) < 0) { perror("pipe"); return 1; }

    // 各コマンドを順番に子プロセスで実行
    for (t_cmd *c=head; c; c=c->next, i++)
    {
        // 入力：最初のコマンドは標準入力、それ以外は前のパイプから
        int in_fd  = (i==0)     ? STDIN_FILENO  : pipes[2*(i-1)];
        // 出力：最後のコマンドは標準出力、それ以外は次のパイプへ
        int out_fd = (i==n-1)   ? STDOUT_FILENO : pipes[2*i + 1];

        pid_t pid = fork();
        if (pid < 0) { perror("fork"); return 1; }
        if (pid == 0) {
            // 子プロセス：使わないパイプの端を全て閉じる
            for (int k=0; k<2*(n-1); k++) if (pipes[k] != in_fd && pipes[k] != out_fd) close(pipes[k]);
            child_exec(c, in_fd, out_fd, env);
        }
        pids[i] = pid;

        // 親プロセス：子に渡したパイプの端を閉じる
        if (i > 0) close(pipes[2*(i-1)]);      // 前のパイプの読み取り端
        if (i < n-1) close(pipes[2*i + 1]);    // 現在のパイプの書き込み端
    }

    // 全ての子プロセスの終了を待機
    int status = 0, last_status = 0;
    for (int k=0; k<n; k++) {
        if (waitpid(pids[k], &status, 0) > 0) {
            // 最後のコマンドの終了ステータスを保存
            if (k == n-1) {
                if (WIFEXITED(status)) last_status = WEXITSTATUS(status);
                else if (WIFSIGNALED(status)) last_status = 128 + WTERMSIG(status);
            }
        }
    }
    return last_status;
}
