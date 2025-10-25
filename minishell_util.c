/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:18:40 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/25 13:36:17 by ayusa            ###   ########.fr       */
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
	char	*line;

	setup_signals_interactive();
	g_sig = 0;
	line = readline("minishell$ ");
	if (!line || (ft_strcmp(line, "exit") == 0)) //EOF(Ctrl-D)
	{
		write(1, "exit\n", 5);
		sh->status = 0;
		return (1);
	}
	if (g_sig == SIGINT)//Ctrl-C
	{
		set_sigint(sh);
		free(line);
		return (0);
	}
	if (*line == '\0')
		return (free(line), 0);
	sh->line = line;
	add_history(line);
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

void	after_oneloop(t_shell *sh)
{
	int i;

	i = 0;
	while (sh->tmpfiles && sh->tmpfiles[i])
	{
		if (unlink(*sh->tmpfiles[i++]) == -1)
			perror("minishell: unlink");//unlink失敗時
	}
	ft_free_str_array(*sh->tmpfiles);

	continue_free(sh); // before:ft_parser()直後だった after:ここで良いかな？(yusa)
	free(sh->line); //ここで解放しないと、どこかの内部(忘れた)でまだline使っててセグフォになる。
	sh->line = NULL;
}

void	after_minishell(t_shell *sh)
{
	clear_history();
	if (sh->line)
		free(sh->line);
	continue_free(sh);
	ft_lst_clear(&sh->env);
	sh->env = NULL;
}
