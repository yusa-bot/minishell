/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:50:36 by rinka             #+#    #+#             */
/*   Updated: 2025/09/15 12:03:47 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig = 0;

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env *env_lst;
	//int g_last_status = 0;
	env_lst = ft_set_env(envp);

	rl_catch_signals = 0;//readlineのデフォルトハンドラを無効化。カスタムのシグナルハンドラを作成しているため。
	setup_signals_interactive();

	char *line;
	while (1)
	{
		g_sig = 0;
		line = readline("$ ");
		if (*line == '\0')// 空ならスキップ（履歴は追加しない）
		{
			free(line);
			continue;
		}
		if (line == NULL)//EOF (Ctrl-D)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}

		/////must test
		if (g_sig == SIGINT)//sigint_handler()後に実行
		{
			g_sig = 0;
			free(line);
			continue;
		}
		add_history(line);
		//////

		t_token *token_lst = tokenize_line(line);
		free(line);
		t_cmd	*cmd_lst = ft_parser(token_lst, env_lst);



	 	////HEREDOCのときのみ専用fdに入れ替える関数を通す。
	 	////ここではcmd_lstを回す。
	 	//while (cmd_lst)
	 	//{
	 	//	prepare_heredoc_for_cmd(cmd_lst, env_lst);
	 	//	cmd_lst = cmd_lst->next;
	 	//}

	 	//ft_tokenlst_clear(&token_lst);
	 	//free(line);
	 	//if (!cmd_lst)
	 	//	continue;




        //if (PIPE)
		// 	//pipe


		////PIPE以外 (とりあえず単独コマンドのみ。)(リダイレクト対応は後で。)
		//if (cmd_lst && run_parent(cmd_lst->cmd_args[0]))
		//	//親
		//if (echo, pwd, env | 外部コマンド)
		//	//fork





	 	ft_cmdlst_clear(&cmd_lst);
	}
	ft_lst_clear(&env_lst);
	// return g_last_status;
	return 0;
}
