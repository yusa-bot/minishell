/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:50:36 by rinka             #+#    #+#             */
/*   Updated: 2025/10/25 13:44:41 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_sig = 0;

void	token_debag(t_token *token_lst);
void	cmd_debag(t_cmd *cmd_lst, int j);
void	heredoc_debag(char **tmpfiles);

int	prompt_to_struct(t_shell *sh)
{
	tokenize_line(sh);//mallocチェックokメモリリークまだ
	if (!sh->token)
	{
		free(sh->line);
		return (0);
	}
	//token_debag(sh.token); //debag
	ft_parser(sh); //syntax or ambiguous error（malloc）は各関数で即free&exit
	if (!sh->cmd)
	{
		ft_tokenlst_clear(&sh->token);
		free(sh->line);
		return (0);
	}
	return (1);
}

void	minishell_loop(t_shell *sh)
{
	while (1)
	{
		if (read_prompt(sh))
			break ;
		else if (!sh->line)
			continue ;
		if (!prompt_to_struct(sh))
			continue;
		//cmd_debag(sh.cmd, loop_count); //debag
		//heredoc_debag(tmpfiles); //debag
		exec_cmd_handler(sh);
		after_oneloop(sh); // 1loopごとの後処理↓
	}
	after_minishell(sh);
}

int main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	(void)argc;
	(void)argv;
	minishell_init(&sh, envp);
	g_sig = 0;
	rl_catch_signals = 0; // シグナルをreadlineではなく自作で制御するため。
	minishell_loop(&sh);
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
