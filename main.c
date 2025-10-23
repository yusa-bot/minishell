/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:50:36 by rinka             #+#    #+#             */
/*   Updated: 2025/10/23 17:35:29 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_env *env_lst;
	t_token *token_lst;
	t_cmd	*cmd_lst;
	t_shell	shell;

	env_lst = ft_set_env(envp);
	cmd_lst = NULL;
	token_lst = NULL;
	shell.env = env_lst;
	shell.status = 0;
	shell.is_pipe = 0; // heredoc由来のredirect 謎 不要かも

	rl_catch_signals = 0;
	setup_signals_interactive();

	char *line;
	char **tmpfiles;
	int loop_count = 0;

	while (1)
	{
		int j = 0;
		line = readline("minishell$ ");
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

		if (ft_strcmp(line, "exit") == 0) // これ別途処理されてないか確認する
		{
			free(line);
			break ;
		}

		token_lst = tokenize_line(line, env_lst);//mallocチェックokメモリリークまだ
		if (!token_lst)
		{
			free(line);
			continue;
		}
		token_debag(token_lst); //debag

		tmpfiles = NULL;
		cmd_lst = ft_parser(token_lst, env_lst, &tmpfiles, &shell);
		if (!cmd_lst)//syntax or ambiguous error（malloc）は各関数で即free&exit
		{
			ft_tokenlst_clear(&token_lst);
			free (line);
			continue ;
		}
		cmd_debag(cmd_lst, j); //debag
		heredoc_debag(tmpfiles); //debag


		// コマンド実行群追加
		if (cmd_lst && cmd_lst->next)
			shell.status = run_pipe(cmd_lst, &env_lst, &shell);
		else if (is_builtin_parent(cmd_lst->cmd_args))
			shell.status = run_parent(cmd_lst, &env_lst, &shell);
		else
			shell.status = run_child(cmd_lst, &env_lst, &shell);


		// 1loopごとの後処理↓
		int i = 0;
		while (tmpfiles &&  tmpfiles[i])
		{
			if (unlink(tmpfiles[i++]) == -1)
				perror("minishell: unlink");//unlink失敗時
		}
		ft_free_str_array(tmpfiles);
		loop_count++;
		continue_free(&token_lst, &cmd_lst); // before:ft_parser()直後だった after:ここで良いかな？(yusa)
		free(line); //ここで解放しないと、どこかの内部(忘れた)でまだline使っててセグフォになる。
	}
	ft_lst_clear(&env_lst);
	shell.env = NULL;
	return (0);
}


void	token_debag(t_token *token_lst)
{
	printf("-----------first_token------------\n");
	t_token *tmp = token_lst;
	while (tmp)
	{
		printf("str: %s\n", tmp->str);
		printf("original_str: %s\n", tmp->original_str);
		printf("token_type: %d\n", tmp->token_type);
		printf("quote_type: %d\n", tmp->quote_type);
		printf("joint_next: %d\n\n", tmp->is_joined_with_next);
		tmp = tmp->next;
	}
	printf("-----------first_token_end------------\n");
	printf("\n");
	if (tmp == NULL)
		printf("null tarminated\n");
}

void	cmd_debag(t_cmd *cmd_lst, int j)
{
	t_cmd	*tmp_cmd = cmd_lst;
	printf("\n↓↓↓以下、パイプ区切りで分けてt_cmdに格納した値↓↓↓\n");
	while (tmp_cmd)
	{
		char **args = tmp_cmd->cmd_args;
		int i = 0;
		printf("[cmd_lst%d個目]\n", ++j);
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
		printf("\n\n");
		printf("files:\n");
		if (tmp_cmd->infile)
		{
			t_redirect *tmp_fileinfo = tmp_cmd->infile;
			while (tmp_fileinfo)
			{
				if (tmp_fileinfo->token_type == HEREDOC)
					printf("<");
				printf("< %s\n", tmp_fileinfo->expanded_arg);
				tmp_fileinfo = tmp_fileinfo->next;
			}
		}
		if (tmp_cmd->outfile)
		{
			t_redirect *tmp_fileinfo = tmp_cmd->outfile;
			while (tmp_fileinfo)
			{
				if (tmp_fileinfo->token_type == APPEND)
					printf(">");
				printf("> %s\n", tmp_fileinfo->expanded_arg);
				tmp_fileinfo = tmp_fileinfo->next;
			}
		}
		printf("\n");
		tmp_cmd = tmp_cmd->next;
	}
	printf("\n");
}

void	heredoc_debag(char **tmpfiles)
{
	int i = 0;
	while (tmpfiles &&  tmpfiles[i])
	{
		printf("↓↓隠しファイル%d個目（%s）に書き込まれた内容↓↓\n", i+1, tmpfiles[i]);
		FILE* fp = fopen(tmpfiles[i], "r");
		int	c = fgetc(fp);
		while (c != EOF)
		{
			write(1, &c, 1);
			c = fgetc(fp);
		}
		printf("\n");
		fclose(fp);
	}
}
