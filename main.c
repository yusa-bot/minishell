/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:50:36 by rinka             #+#    #+#             */
/*   Updated: 2025/09/27 19:01:26 by ayusa            ###   ########.fr       */
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

	env_lst = ft_set_env(envp);

	cmd_lst = NULL;
	token_lst = NULL;
	shell.env = env_lst;
	shell.status = 0;
	rl_catch_signals = 0;
	setup_signals_interactive();

	char *line;
	while (1)
	{
		g_sig = 0;
		line = readline("$ ");
		if (line == NULL)//EOF(Ctrl-D)
		{
			printf("EOF\n");
			if (loop_count > 0)
			{
				continue_free(&token_lst, &cmd_lst);
				free(line);
				ft_lst_clear(&env_lst);
				shell.env = NULL;
				rl_clear_history();
			}

			write(1, "exit\n", 5);
			exit(shell.status);
		}
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		if (g_sig == SIGINT)//Ctrl-C
		{
			printf("SIGINT\n");
			g_sig = 0;
			free(line);
			continue;
		}
		if (*line)
			add_history(line);

		token_lst = tokenize_line(line);
		if (!token_lst)
		{
			free(line);
			continue;
		}
		cmd_lst = ft_parser(token_lst, env_lst, &shell);
		if (!cmd_lst)
		{
			ft_tokenlst_clear(&token_lst);
			free(line);
			continue;
		}


	 	//内部でheredocを判定
	 	//ここではcmd_lstを回す。
	 	while (cmd_lst)
	 	{
	 		prepare_heredoc_for_cmd(cmd_lst, env_lst);
	 		cmd_lst = cmd_lst->next;
	 	}


        if (cmd_lst && cmd_lst->next)
			shell.status = run_pipe(cmd_lst, &env_lst, &shell);
		else if (is_builtin_parent(cmd_lst->cmd_args))
		{
			shell.status = run_parent(cmd_lst, &env_lst, &shell);
			printf("main");
		}
		else
			shell.status = run_child(cmd_lst, &env_lst, &shell);
		continue_free(&token_lst, &cmd_lst);
		loop_count++;
		free(line);
	}
	ft_lst_clear(&env_lst);
	shell.env = NULL;
	return shell.status;
}
