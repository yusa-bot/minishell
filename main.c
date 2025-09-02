/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:50:36 by rinka             #+#    #+#             */
/*   Updated: 2025/09/02 09:29:20 by rinka            ###   ########.fr       */
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
		
		t_token *token_lst = tokenize_line(line);
		t_cmd	*cmd_lst = ft_parser(token_lst, env_lst);
		// (void) cmd_lst;
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
				printf("< %s\n", tmp_cmd->infile);
			if (tmp_cmd->outfile)
				printf("> %s\n", tmp_cmd->outfile);
			if (tmp_cmd->append == 1)
				printf("append: Yes\n");
			else
				printf("append: No\n");
			printf("\n");
			tmp_cmd = tmp_cmd->next;
		}
		printf("\n");
		// if (tmp == NULL) 
		// 	printf("null tarminated\n");
		printf("%s\n", line);
		free(line);

		ft_cmdlst_clear(&cmd_lst);
	}

	//parserでt_cmdに
	// t_cmd *cmd_lst = parse_tokens(token_lst, env_lst);
	// ft_tokenlst_clear(&tcmds_lst);

	//t_envのfree
	ft_envlst_clear(&env_lst);
	
	
	return (0);
}

// int main(int argc, char **argv, char **envp)//"export TEST=/test/pathでテスト"
// {
// 	t_env *env_lst;
// 	(void)argc;

// 	env_lst = NULL;
// 	env_lst = set_env(envp);

// 	int env_fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (env_fd == -1)
// 	{
// 		return (1);
// 	}

// 	//export TEST=/test/path
// 	ft_add_env(&env_lst, "TEST=/test/path", 1);
// 	//export TEST2=/test2/path
// 	ft_add_env(&env_lst, "TEST2=/test2/path", 0);

// 	//unset前
// 	ft_put_envs(env_lst, env_fd);//順番？？
// 	write(env_fd, "\n", 1);
// 	ft_put_exports(env_lst, env_fd);
// 	write(env_fd, "\n", 1);

// 	int unset_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (unset_fd == -1)
// 	{
// 		return (1);
// 	}

// 		//TEST=/test/pathをunset
// 	ft_unset(&env_lst, "TEST");

// 	//unset後
// 	ft_put_envs(env_lst, unset_fd);
// 	write(unset_fd, "\n", 1);
// 	ft_put_exports(env_lst, unset_fd);

// 	//t_envのfree
// 	ft_envlst_clear(&env_lst);
// }

