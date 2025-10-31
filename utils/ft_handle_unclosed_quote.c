/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_unclosed_quote.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:39:01 by rinka             #+#    #+#             */
/*   Updated: 2025/10/31 16:07:57 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_is_quote_closed(char *line)
{
	int i;
	t_quote_type current_quote;

	i = 0;
	current_quote = NONE;
	while (line[i])
	{
		if (line[i] == '"')
		{
			if (current_quote == NONE)
				current_quote = DOUBLE;
			else if (current_quote == DOUBLE)
				current_quote = NONE;
		}
		else if (line[i] == '\'')
		{
			if (current_quote == NONE)
				current_quote = SINGLE;
			else if (current_quote == SINGLE)
				current_quote = NONE;
		}
		i++;
	}
	if (current_quote != NONE)
		return (0);
	return (1);
}


void ft_handle_unclosed_quote(t_shell *sh)
{
	char *line;
	char *str;

	line = ft_strdup(sh->line);
	if (line == NULL)
		malloc_error(sh, NULL);
	while (!ft_is_quote_closed(line))
	{
		str = readline("> ");
		line = ft_strjoin_safe(line, "\n");
		if (line)
			line = ft_strjoin_safe(line, str);
		free(str);
		if (line == NULL)
			malloc_error(sh, NULL);
	}
	free(sh->line);
	sh->line = line;
}
