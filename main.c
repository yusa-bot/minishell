/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:50:36 by rinka             #+#    #+#             */
/*   Updated: 2025/10/10 13:30:35 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_env *env_lst;
	(void)argc;
	(void)argv;

	env_lst = set_env(envp);
	
	//------------------以下、tokenizer--------------------------------

	char *line;
	while (1)
	{
		int j = 0;
		line = readline("$ ");
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

		
		t_cmd	*cmd_lst = ft_parser(token_lst, env_lst);
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
				printf("args%d %s\n", i, args[i]);
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
					printf("< %s\n", tmp_fileinfo->expanded_filename);
					tmp_fileinfo = tmp_fileinfo->next;
				}
			}
			if (tmp_cmd->outfile)
			{
				t_redirect *tmp_fileinfo = tmp_cmd->outfile;
				while (tmp_fileinfo)
				{
					printf("> %s\n", tmp_fileinfo->expanded_filename);
					if (tmp_fileinfo->token_type == APPEND)
						printf("(Append)\n");
					tmp_fileinfo = tmp_fileinfo->next;
				}
			}
			printf("\n");
			tmp_cmd = tmp_cmd->next;
		}
		printf("\n");
		// if (tmp == NULL) 
		// 	printf("null tarminated\n");
		printf("%s\n", line);////////////////////
		free(line);

		ft_cmdlst_clear(&cmd_lst);
		ft_tokenlst_clear(&token_lst);
	}

	//parserでt_cmdに
	// t_cmd *cmd_lst = parse_tokens(token_lst, env_lst);

	//t_envのfree
	ft_envlst_clear(&env_lst);
	return (0);
}
