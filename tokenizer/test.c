/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 07:50:36 by rinka             #+#    #+#             */
/*   Updated: 2025/08/15 11:13:35 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_perser.h"

int main()
{
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
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			printf("exit\n");
		}

	// 		t_token *new;
	// t_token_type token_type;
	// t_quote_type quote_type;
	// char *str;

	// str = line;
	// token_type = 0;
	// quote_type = 0;

	
	// new = ft_tokenlst_new(str, token_type, quote_type);
		
		t_token *token_lst = tokenize_line(line);
		t_token *tmp = token_lst;
		int i = 0;
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
	return (0);
}
