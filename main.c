/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:50:36 by rinka             #+#    #+#             */
/*   Updated: 2025/10/23 09:08:36 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_env *env_lst;
	(void)argc;
	(void)argv;

	env_lst = ft_set_env(envp);

	//------------------以下、tokenizer--------------------------------

	char *line;
	while (1)
	{
		int j = 0;
		line = readline("minishell$ ");
		if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
		{
			add_history(line);
		}
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}

		t_token *token_lst = tokenize_line(line, env_lst);//mallocチェックokメモリリークまだ
		// printf("-----------first_token------------\n");
		// t_token *tmp = token_lst;
		// while (tmp)/////
		// {
		// 	printf("str: %s\n", tmp->str);
		// 	printf("original_str: %s\n", tmp->original_str);
		// 	printf("token_type: %d\n", tmp->token_type);
		// 	printf("quote_type: %d\n", tmp->quote_type);
		// 	printf("joint_next: %d\n\n", tmp->is_joined_with_next);
		// 	tmp = tmp->next;
		// }
		// printf("-----------first_token_end------------\n");
		// printf("\n");/////
		// if (tmp == NULL)
		// 	printf("null tarminated\n");///////

		char **tmpfiles;
		tmpfiles = NULL;

		t_cmd	*cmd_lst = ft_parser(token_lst, env_lst, &tmpfiles);
		if (cmd_lst == NULL)//syntax or ambiguous error（malloc）は各関数で即free&exit
		{
			ft_tokenlst_clear(&token_lst);
			free (line);
			continue ;
		}
		// (void) cmd_lst;
		t_cmd	*tmp_cmd = cmd_lst;///////////////
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
					printf("< %s\n", tmp_fileinfo->expanded_argi);
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
					printf("> %s\n", tmp_fileinfo->expanded_argi);
					tmp_fileinfo = tmp_fileinfo->next;
				}
			}
			printf("\n");
			tmp_cmd = tmp_cmd->next;
		}
		printf("\n");
		// if (tmp == NULL)
		// 	printf("null tarminated\n");
		free(line);

		ft_cmdlst_clear(&cmd_lst);
		ft_tokenlst_clear(&token_lst);
		int i = 0;

		while (tmpfiles &&  tmpfiles[i])
		{
			printf("↓↓隠しファイル%d個目（%s）に書き込まれた内容↓↓\n", i+1, tmpfiles[i]);
			FILE* fp = fopen(tmpfiles[i], "r");
			int c;
			c = fgetc(fp);
			while (c != EOF)
			{
				write(1, &c, 1);
				c = fgetc(fp);
			}
			printf("\n");
			fclose(fp);
			if (unlink(tmpfiles[i++]) == -1)
				perror("minishell: unlink");//unlink失敗時
		}
		ft_free_str_array(tmpfiles);
	}

	//parserでt_cmdに
	// t_cmd *cmd_lst = parse_tokens(token_lst, env_lst);

	//t_envのfree
	ft_lst_clear(&env_lst);
	return (0);
}
