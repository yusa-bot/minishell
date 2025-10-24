/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:50:36 by rinka             #+#    #+#             */
/*   Updated: 2025/10/24 15:29:10 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_debag(t_token *token_lst);
void	cmd_debag(t_cmd *cmd_lst, int j);
void	heredoc_debag(char **tmpfiles);

void	minishell_init(t_shell *sh, char **envp, char ***tmpfiles)
{
	sh->env = NULL; //初期化をrinkaがやっているか確認
	sh->cmd = NULL;
	sh->env = ft_set_env(envp);
	sh->status = 0;
	sh->line = NULL;
	tmpfiles = NULL;
}

void	set_sigint(t_shell *sh)
{
	sh->status = 130; //マクロ化
	rl_replace_line("", 0);//readline の入力行をクリア
	rl_on_new_line();//readline ライブラリに「カーソルが新しい行に移動した」ことを通知
	rl_redisplay();//入力待ち状態を再表示
}

after_oneloop(t_shell *sh, char	**tmpfiles)
{
	int i;

	i = 0;
	while (tmpfiles &&  tmpfiles[i])
	{
		if (unlink(tmpfiles[i++]) == -1)
			perror("minishell: unlink");//unlink失敗時
	}
	ft_free_str_array(tmpfiles);

	continue_free(sh); // before:ft_parser()直後だった after:ここで良いかな？(yusa)
	free(sh->line); //ここで解放しないと、どこかの内部(忘れた)でまだline使っててセグフォになる。
	sh->line = NULL;
}

after_minishell(t_shell *sh)
{
	cear_history();
	if (sh->line)
		free(sh->line);
	continue_free(&sh);
	ft_lst_clear(&sh->env);
	sh->env = NULL;
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
		set_sigint(&sh);
		free(line);
		return (0);
	}
	if (*line == '\0')
		return (free(line), 0);
	sh->line = line;
	add_history(line);
	return (0);
}

exec_cmd_handler(t_shell *sh)
{
	if (sh->cmd && sh->cmd->next)
		sh->status = run_pipe(&sh);
	else if (is_builtin_parent(sh->cmd->cmd_args))
		sh->status = run_parent(&sh);
	else
		sh->status = run_child(&sh);
}

int main(int argc, char **argv, char **envp)
{
	char	**tmpfiles;
	int		is_continue;
	int		loop_count;
	t_shell	sh;

	(void)argc;
	(void)argv;
	minishell_init(&sh, envp, &tmpfiles);
	loop_count = 0;
	is_continue = 0;
	rl_catch_signals = 0; // シグナルをreadlineではなく自作で制御するため。
	while (1)
	{
		is_continue = read_prompt(&sh);
		if (read_prompt(&sh))
			break ;
		else if (!sh.line)
			continue ;
		sh.token = tokenize_line(sh.line, sh.env);//mallocチェックokメモリリークまだ
		if (!sh.token)
		{
			free(sh.line);
			continue;
		}
		//token_debag(sh.token); //debag
		sh.cmd = ft_parser(&sh, &tmpfiles);
		if (!sh.cmd)//syntax or ambiguous error（malloc）は各関数で即free&exit
		{
			ft_tokenlst_clear(&sh.token);
			free (sh.line);
			continue ;
		}
		//cmd_debag(sh.cmd, loop_count); //debag
		//heredoc_debag(tmpfiles); //debag
		exec_cmd_handler(&sh);
		after_oneloop(&sh, tmpfiles); // 1loopごとの後処理↓
		loop_count++;
	}
	after_minishell(&sh);
	return (sh.status);
}


void	token_debag(t_token *token_lst)
{
	printf("-----------token debag------------\n");
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
	printf("\n");
	if (tmp == NULL)
		printf("null tarminated\n");
}

void	cmd_debag(t_cmd *cmd_lst, int j)
{
	t_cmd	*tmp_cmd = cmd_lst;
	printf("----------cmd debag------------\n");
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
		printf("-----------heredoc debag------------\n");
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
		i++;
	}
}
