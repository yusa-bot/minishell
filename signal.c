/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:38:45 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/07 19:45:20 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <signal.h>

//SIGINT: Ctrl+C
//SIGQUIT: Ctrl+\
//SIG_DFL: デフォルトの動作

//Ctrl+C
void	sigint_handler(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	//Readline ライブラリが提供する既存の関数
	rl_replace_line("", 0);//readline の入力行をクリア
	rl_on_new_line();//新しい行に移動
	rl_redisplay();//入力待ち状態を再表示
}

//ctrl-C & ctrl-\ 設定
void setup_signals_interactive(void)
{
    struct sigaction sa = {0};
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);   // ctrl-Cのみ細かくsigaction
    signal(SIGQUIT, SIG_IGN);       // ctrl-\ 何もしない
}

//子プロセス（コマンド実行時など）でシグナルの挙動を「デフォルト」に戻す
void setup_signals_child(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}
