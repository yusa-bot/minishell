/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:50:36 by rinka             #+#    #+#             */
/*   Updated: 2025/08/25 08:48:59 by rinka            ###   ########.fr       */
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
		t_token *tmp = token_lst;
		while (tmp)
		{
			printf("str: %s\n", tmp->str);
			printf("token_type: %d\n", tmp->token_type);
			printf("quote_type: %d\n", tmp->quote_type);
			printf("joint_next: %d\n\n", tmp->is_joined_with_next);
			tmp = tmp->next;
		}
		printf("\n");
		if (tmp == NULL) 
			printf("null tarminated\n");
		printf("%s\n", line);
		free(line);
		ft_tokenlst_clear(&token_lst);
	}

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

