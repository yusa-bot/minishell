/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:50:36 by rinka             #+#    #+#             */
/*   Updated: 2025/09/14 13:18:11 by ayusa            ###   ########.fr       */
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
	env_lst = set_env(envp);

	rl_catch_signals = 0;//readlineのデフォルトハンドラを無効化。カスタムのシグナルハンドラを作成しているため。
	setup_signals_interactive();

	char *line;
	while (1)
	{
		g_sig = 0;
		line = readline("$ ");
		if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}

		//sigint_handler()後に実行
		if (g_sig == SIGINT)
		{
			g_sig = 0;
			free(line);
			continue;
		}
		// 空ならスキップ（履歴は追加しない）
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		add_history(line);

		t_token *token_lst = tokenize_line(line);
		free(line);
		t_cmd	*cmd_lst = ft_parser(token_lst, env_lst);


		///////////
		t_cmd	*tmp_cmd = cmd_lst;
		printf("\n↓↓↓以下、パイプ区切りで分けてt_cmdに格納した値↓↓↓\n");
		while (tmp_cmd)
		{
			char **args = tmp_cmd->cmd_args;
			int i = 0;
			printf("[cmd_lst%d個目]\n", i+1);
			printf("args:");
			while (args && args[i])
			{
				printf(" %s", args[i]);
				i++;
			}
			printf("\n");
			args = tmp_cmd->env_vars;
			i = 0;
			printf("vars:");
			while (args && args[i])
			{
				printf(" %s", args[i]);
				i++;
			}
			printf("\n");
			if (tmp_cmd->infile)
			{
				t_redirect *tmp_fileinfo = tmp_cmd->infile;
				while (tmp_fileinfo)
				{
					printf("< %s\n", tmp_fileinfo->expanded_str);
					tmp_fileinfo = tmp_fileinfo->next;
				}
			}
			if (tmp_cmd->outfile)
			{
				t_redirect *tmp_fileinfo = tmp_cmd->outfile;
				while (tmp_fileinfo)
				{
					printf("> %s\n", tmp_fileinfo->expanded_str);
					if (tmp_fileinfo->token_type == APPEND)
						printf("(Append)\n");
					tmp_fileinfo = tmp_fileinfo->next;
				}
			}
			printf("\n");
			tmp_cmd = tmp_cmd->next;
		}
		printf("\n");
		printf("%s\n", line);
		///////////////


	// 	//HEREDOCのときのみ専用fdに入れ替える関数を通す。
	// 	//ここではcmd_lstを回す。
	// 	while (cmd_lst)
	// 	{
	// 		prepare_heredoc_for_cmd(cmd_lst, env_lst);
	// 		cmd_lst = cmd_lst->next;
	// 	}

	// 	ft_tokenlst_clear(&token_lst);
	// 	free(line);
	// 	if (!cmd_lst)
	// 		continue;

    //     if (!cmd_lst->next && cmd_lst->cmd_args && cmd_lst->cmd_args[0]
    //         && is_builtin_name(cmd_lst->cmd_args[0]) && must_run_in_parent(cmd_lst->cmd_args[0]))
    //     {
    //         g_last_status = run_single_builtin_in_parent(cmd_lst, &env_lst);
    //     }
    //     else
    //     {
    //         g_last_status = execute_pipeline(cmd_lst, &env_lst);
    //     }

	 	ft_cmdlst_clear(&cmd_lst);
	}
	ft_envlst_clear(&env_lst);
	// return g_last_status;
	return 0;
}
