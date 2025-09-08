/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:40:06 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/08 22:01:45 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 環境変数の展開（ダミー・フック。あなたの既存expandに置き換えてOK）
static char *expand_vars(const char *line, /* envや$? など必要なら */ void *env)
{
    (void)env;
    // ここに既存の展開ロジックを繋ぐ。
    // ひとまず何もしないパススルー
    return strdup(line);
}

// SIGINT中断処理用のフラグ（あなたのグローバルに合わせて調整）
static volatile sig_atomic_t g_heredoc_interrupted = 0;

static void heredoc_sigint(int signo)
{
    (void)signo;
    g_heredoc_interrupted = 1;
    // readline系は行頭に改行を表示させたいのでここで何もしない or write(1,"\n",1)
}

// delimiterまで読み込み、pipeのread側FDを返す。失敗時 -1
static int build_heredoc_fd(const char *raw_delim, int do_expand, void *env)
{
    int fds[2];
    char *line = NULL;
    char *delim = NULL;

    if (pipe(fds) < 0) return -1;

    // 既定：SIGINTで中断できるよう一時的に簡易ハンドラ
    struct sigaction sa_old_int, sa_new;
    memset(&sa_new, 0, sizeof(sa_new));
    sa_new.sa_handler = heredoc_sigint;
    sigemptyset(&sa_new.sa_mask);
    sa_new.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_new, &sa_old_int);

    g_heredoc_interrupted = 0;

    // delimiterのクォートを外した実体
    delim = unquote_all(raw_delim);
    if (!delim) { close(fds[0]); close(fds[1]); sigaction(SIGINT, &sa_old_int, NULL); return -1; }

    while (!g_heredoc_interrupted) {
        line = readline("> ");
        if (!line) break; // EOF (^D) → そのまま終了
        if (strcmp(line, delim) == 0) { free(line); line=NULL; break; }

        char *out = NULL;
        if (do_expand) out = expand_vars(line, env);
        else           out = strdup(line);
        free(line); line=NULL;
        if (!out) { g_heredoc_interrupted = 1; break; }

        // 行+改行を書き込む
        write(fds[1], out, strlen(out));
        write(fds[1], "\n", 1);
        free(out);
    }

    free(delim);
    // 書き込み側を閉じて入力完了を示す
    close(fds[1]);

    // SIGINTハンドラを元に戻す
    sigaction(SIGINT, &sa_old_int, NULL);

    if (g_heredoc_interrupted) {
        close(fds[0]);
        return -1; // 呼び出し側で status=130 等にしてください
    }
    return fds[0]; // これを STDIN にdup2すればOK
}

// 親でコマンド実行前に呼ぶ：HEREDOCをpipeのread FDに置き換える
int prepare_heredocs_for_cmd(t_cmd *cmd, void *env)
{
	t_redirect *r = cmd->infile;
    while (r)
	{
        if (r->token_type == HEREDOC)
		{
            int expand = !is_quoted_delim(r->arg); // クォートあり→展開しない（bash準拠）
            int fd = build_heredoc_fd(r->arg, expand, env);
            if (fd < 0) return -1; // 中断や失敗。呼び出し側で全体の実行を中止する
            r->prepared_fd = fd;

            // apply_redirectionsで通常入力扱いにするため、型をINFILEに差し替える手もあり
            r->token_type = INFILE;
            // argは使わないが、後片付けポリシーに応じて保持/解放を判断
        }
		r->next
    }
    return 0;
}
