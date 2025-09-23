/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:50:36 by rinka             #+#    #+#             */
/*   Updated: 2025/09/23 15:28:20 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig = 0;

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_env *env_lst;
	t_cmd *cmd_lst;
	t_token *token_lst;

	t_shell shell;
	int loop_count = 0;

	env_lst = ft_set_env(envp);//t_env malloc
	// int i = 0;
	// while (env_lst && env_lst->next)
    // {
    //     printf("[%d] key=%s | value=%s | is_export=%d | next=%p\n",
    //         i, env_lst->key, env_lst->value, env_lst->is_export, (void *)env_lst->next);
    //     env_lst = env_lst->next;
    //     i++;
    // }

	shell.env = env_lst;
	shell.status = 0;
	rl_catch_signals = 0;
	setup_signals_interactive();

	char *line;
	while (1)
	{
		printf("[[loop top shell status: %d]]\n", shell.status);
		g_sig = 0;
		line = readline("$ ");
		if (line == NULL)//EOF(Ctrl-D)
		{
			printf("EOF\n");
			if (loop_count > 0)
			{
				rl_clear_history();
				free(line);
				continue_free(&token_lst, &cmd_lst, &env_lst);
			}
			write(1, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
		if (*line == '\0')
		{
			free(line);
			continue_free(&token_lst, &cmd_lst, &env_lst);
			continue;
		}
		if (g_sig == SIGINT)//Ctrl-C
		{
			printf("SIGINT\n");
			g_sig = 0;
			free(line);
			continue_free(&token_lst, &cmd_lst, &env_lst);
			continue;
		}
		if (*line)
			add_history(line);


		//token, parserのエラー処理（free）は任せたい。
		token_lst = tokenize_line(line);
		if (!token_lst)
		{
			printf("token_lst null");//
			continue_free(&token_lst, &cmd_lst, &env_lst);
			continue;
		}
		cmd_lst = ft_parser(token_lst, env_lst, &shell);
		if (!cmd_lst)
		{
			printf("cmd_lst null");//
			continue_free(&token_lst, &cmd_lst, &env_lst);
			continue;
		}




		// int i = 0;
		// t_cmd	*tmp_cmd = cmd_lst;
		// printf("\n↓↓↓以下、パイプ区切りで分けてt_cmdに格納した値↓↓↓\n");
		// while (tmp_cmd)
		// {
		// 	char **args = tmp_cmd->cmd_args;
		// 	i = -1;
		// 	printf("[cmd_lst%d個目]\n", i+1);
		// 	i++;
		// 	printf("args:");
		// 	while (args && args[i])
		// 	{
		// 		printf(" %s", args[i]);
		// 		i++;
		// 	}
		// 	printf("\n");

		// 	args = tmp_cmd->env_vars;
		// 	i = 0;
		// 	printf("vars:");
		// 	while (args && args[i])
		// 	{
		// 		printf(" %s", args[i]);
		// 		i++;
		// 	}
		// 	printf("\n");

		// 	if (tmp_cmd->infile)
		// 	{
		// 		t_redirect *tmp_fileinfo = tmp_cmd->infile;
		// 		while (tmp_fileinfo)
		// 		{
		// 			printf("< %s\n", tmp_fileinfo->expanded_str);
		// 			tmp_fileinfo = tmp_fileinfo->next;
		// 		}
		// 	}
		// 	if (tmp_cmd->outfile)
		// 	{
		// 		t_redirect *tmp_fileinfo = tmp_cmd->outfile;
		// 		while (tmp_fileinfo)
		// 		{
		// 			printf("> %s\n", tmp_fileinfo->expanded_str);
		// 			if (tmp_fileinfo->token_type == APPEND)
		// 				printf("(Append)\n");
		// 			tmp_fileinfo = tmp_fileinfo->next;
		// 		}
		// 	}
		// 	printf("\n");
		// 	tmp_cmd = tmp_cmd->next;
		// }
		// printf("\n");



	 	////HEREDOCのときのみ専用fdに入れ替える関数を通す。
	 	////ここではcmd_lstを回す。
	 	// while (cmd_lst)
	 	// {
	 	// 	prepare_heredoc_for_cmd(cmd_lst, env_lst);
	 	// 	cmd_lst = cmd_lst->next;
	 	// }
	 	// ft_tokenlst_clear(&token_lst);



        if (cmd_lst && cmd_lst->next)
		{
			printf("[[pipe in]]\n");
			shell.status = run_pipe(cmd_lst, &env_lst, &shell);
			printf("[[status code in main: %d]]\n", shell.status);
			if (shell.status != EXIT_SUCCESS)
			{
				continue_free(&token_lst, &cmd_lst, &env_lst);
				continue;
			}
		}
		else if (is_builtin_parent(cmd_lst->cmd_args))
		{
			printf("[[parent in]]\n");
			shell.status = run_parent(cmd_lst, &env_lst, &shell);
			printf("[[status code in main: %d]]\n", shell.status);
			if (shell.status != EXIT_SUCCESS)
			{
				continue_free(&token_lst, &cmd_lst, &env_lst);
				continue;
			}
		}
		else
		{
			printf("[[child in]]\n");
			shell.status = run_child(cmd_lst, &env_lst, &shell);
			printf("[[status code in main: %d]]\n", shell.status);
			if (shell.status != EXIT_SUCCESS)
			{
				continue_free(&token_lst, &cmd_lst, &env_lst);
				continue;
			}
		}
		ft_tokenlst_clear(&token_lst);
		ft_cmd_clear(&cmd_lst);
		loop_count++;
		free(line);
		line = NULL;
	}
	ft_lst_clear(&env_lst);
	shell.env = NULL;
	return shell.status;
}
