/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:18:40 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/26 12:41:40 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_sigint(t_shell *sh)
{
	sh->status = 130; //マクロ化
	rl_replace_line("", 0);//readline の入力行をクリア
	rl_on_new_line();//readline ライブラリに「カーソルが新しい行に移動した」ことを通知
	rl_redisplay();//入力待ち状態を再表示
}

int	read_prompt(t_shell *sh)
{
	setup_signals_interactive();
	g_sig = 0;
	sh->line = readline("minishell$ ");
	if (!sh->line || (ft_strcmp(sh->line, "exit") == 0)) //EOF(Ctrl-D)
	{
		write(1, "exit\n", 5);
		sh->status = 0;
		return (1);
	}
	if (g_sig == SIGINT)//Ctrl-C
	{
		set_sigint(sh);
		free(sh->line);
		sh->line = NULL;
		return (0);
	}
	if (*sh->line == '\0')
	{
		free(sh->line);
		sh->line = NULL;
		return (0);
	}
	add_history(sh->line);
	return (0);
}

void	minishell_init(t_shell *sh, char **envp)
{
	sh->env = NULL;
	sh->env = ft_set_env(envp);
	sh->token = NULL;
	sh->cmd = NULL;
	sh->status = 0;
	sh->line = NULL;
	sh->tmpfiles = NULL;
}

void	after_oneloop_cleanup(t_shell *sh)
{
	int	i;

	write(STDOUT_FILENO, "\033[?2004l", 7);
	continue_free(sh);
	if (sh->line)
	{
		free(sh->line);//ここで解放しないと、どこかの内部(忘れた)でまだline使っててセグフォになる。
		sh->line = NULL;
	}
	if (sh->tmpfiles)
	{
		i = 0;
		while (sh->tmpfiles && sh->tmpfiles[i])
		{
			if (unlink(sh->tmpfiles[i++]) == -1)
				perror("minishell: unlink");//unlink失敗時
		}
		free_split(sh->tmpfiles);
		sh->tmpfiles = NULL;
	}
}

