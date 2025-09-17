/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:50:36 by rinka             #+#    #+#             */
/*   Updated: 2025/09/17 22:13:24 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig = 0;

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env *env_lst;
	t_shell shell;
	t_token *token_lst;
	t_cmd *cmd_lst;
	shell.status = 0;
	env_lst = ft_set_env(envp);//t_env malloc
	shell.env = env_lst;
	rl_catch_signals = 0;
	setup_signals_interactive();

	char *line;
	while (1)
	{
		g_sig = 0;
		line = readline("$ ");
		if (*line == '\0')
		{
			free(line);
			continue_free(token_lst, cmd_lst);
			continue;
		}
		if (line == NULL)//EOF(Ctrl-D)
		{
			rl_clear_history();
			free(line);
			ft_lst_clear(&env_lst);
			write(1, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
		if (g_sig == SIGINT)//Ctrl-C
		{
			g_sig = 0;
			free(line);
			continue_free(token_lst, cmd_lst);
			continue;
		}
		add_history(line);
		//token, parserのエラー処理（free）は任せたい。
		token_lst = tokenize_line(line);
		free(line);
		cmd_lst = ft_parser(token_lst, env_lst);

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

        if (cmd_lst && cmd_lst->next)
		{
			if (!(run_pipe(cmd_lst, &env_lst, shell)))
			{
				continue_free(cmd_lst, token_lst, &env_lst);
				shell.status = EXIT_FAILURE;
				continue;
			}
		}
		else if (is_parent(cmd_lst->cmd_args))
		{
			if (!(run_parent(cmd_lst, &env_lst, shell)))
			{
				continue_free(cmd_lst, token_lst, &env_lst);
				shell.status = EXIT_FAILURE;
				continue;
			}
		}
		else
		{
			if (!(exec_child(cmd_lst, &env_lst, shell)))
			{
				continue_free(cmd_lst, token_lst, &env_lst);
				shell.status = EXIT_FAILURE;
				continue;
			}
		}
	 	ft_cmdlst_clear(&cmd_lst);
	}
	ft_lst_clear(&env_lst);
	return shell.status;
}
