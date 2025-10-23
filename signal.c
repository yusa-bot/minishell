/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:38:45 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/23 10:07:12 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//子プロセス（コマンド実行時など）でシグナルの挙動を「デフォルト」に戻す
void setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

//Ctrl+C
void	sigint_handler(int signo)
{
	(void)signo; //この関数はSIGINT専用のため不要
	g_sig = SIGINT;
	write(STDOUT_FILENO, "\n", 1);//標準出力に改行を出力

	//Readline ライブラリが提供する既存の関数↓
	rl_replace_line("", 0);//readline の入力行をクリア
	rl_on_new_line();//readline ライブラリに「カーソルが新しい行に移動した」ことを通知
	rl_redisplay();//入力待ち状態を再表示
}

//ctrl-C & ctrl-\ 設定
void setup_signals_interactive(void)
{
	struct sigaction sa;
	ft_memset(&sa, 0, sizeof(sa));//
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;//Ctrl+Cを押してもreadlineが中断されず、シェルのプロンプトが正常に継続する
	sigaction(SIGINT, &sa, NULL);   // ctrl-Cのみ細かくsigaction -> sigint_handler()
	signal(SIGQUIT, SIG_IGN);       // ctrl-\ 何もしない
}

//シグナルは用途に応じて名前と番号が決まっている↓
//SIGINT : キーボードからの割り込み(Ctrl+C)2
//SIGQUIT : キーボードからの終了(Ctrl+\)

//SIG_DFL: デフォルトの動作
//SIG_IGN(ignore) : 受け取ったら無視
