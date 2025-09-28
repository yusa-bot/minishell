/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:50:36 by rinka             #+#    #+#             */
/*   Updated: 2025/09/28 13:43:35 by ayusa            ###   ########.fr       */
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
	shell.is_pipe = 0;
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


		// while (cmd_lst)
		// {
		// 	printf("cmd_lst->cmd_args[0]: %s\n", cmd_lst->cmd_args[0]);
		// 	cmd_lst = cmd_lst->next;
		// }

		// while (cmd_lst)
		// {
		// 	if (!cmd_lst->infile)
		// 		continue;
		// 	else
		// 	{
		// 		t_redirect *r = cmd_lst->infile;
		// 		while (r)
		// 		{
		// 			printf("infile: %s\n", r->original_str);
		// 			printf("expanded: %s\n", r->expanded_str);
		// 			r = r->next;
		// 		}
		// 	}
		// 	cmd_lst = cmd_lst->next;
		// }



		shell.status = prepare_heredocs(cmd_lst);

        if (cmd_lst && cmd_lst->next)
		{
			shell.status = run_pipe(cmd_lst, &env_lst, &shell);
		}
		else if (is_builtin_parent(cmd_lst->cmd_args))
		{
			shell.status = run_parent(cmd_lst, &env_lst, &shell);
		}
		else
		{
			shell.status = run_child(cmd_lst, &env_lst, &shell);
		}
		continue_free(&token_lst, &cmd_lst);
		if (cmd_lst && cmd_lst->infile && cmd_lst->infile->heredoc_fd >= 0)
			close(cmd_lst->infile->heredoc_fd);
		loop_count++;
		free(line);
	}
	ft_lst_clear(&env_lst);
	shell.env = NULL;
	return shell.status;
}
