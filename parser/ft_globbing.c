/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_globbing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:11:28 by rinka             #+#    #+#             */
/*   Updated: 2025/10/23 18:31:51 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_match(const char *pattern, const char *filename)
{
	if (*pattern == '\0' && *filename == '\0')
		return (1);
	if (*pattern == '?')
	{
		if (*filename != '\0')
			return (is_match(pattern + 1, filename + 1));
		return (0);
	}
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (*pattern == '\0')
			return (1);
		while (*filename != '\0')
		{
			if (is_match(pattern, filename))
				return (1);
			filename++;
		}
		return (is_match(pattern, filename));
	}
	if (*pattern == *filename)
		return (is_match(pattern + 1, filename + 1));
	return (0);
}

t_token *glob_single_token(char *pattern)
{
	t_token *res_lst;
	DIR	*dirp;
	struct dirent	*dp;
	char *new_str;

	res_lst = NULL;
	dirp =	opendir(".");
	if (dirp == NULL)
	{
		return NULL;
	}
	while ((dp = readdir(dirp)) != NULL)
	{
		if (dp->d_name[0] == '.')
			continue;
		if (is_match(pattern, dp->d_name))
		{
			new_str = ft_strdup(dp->d_name);
			ft_tokenlst_add_back(&res_lst, ft_tokenlst_new(new_str, WORD, NONE, 0));
		}
	}
	closedir(dirp);
	if (!res_lst)
		res_lst = ft_tokenlst_new(ft_strdup(pattern), WORD, NONE, 0);
	return (res_lst);
}

void ft_globbing(t_token **token_list_ptr, int *arg_count)
{
	t_token *current;
	t_token *to_add;
	t_token *next;
	t_token *prev;

	current = *token_list_ptr;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (current->token_type == WORD && (ft_strchr(current->str, '?') || ft_strchr(current->str, '*')))
		{
			to_add = glob_single_token(current->str);
			if (to_add == NULL)
			{
				//エラー処理
			}
			to_add = ft_tokenlst_sort(to_add);
			*arg_count += ft_tokenlst_size(to_add) - 1;
			// ↓展開前のノード一つを消し、そこにglob_single_tokenの返したリストを挿入する
			next = current->next;
			ft_tokenlst_delone(current);
			if (prev)
				prev->next = to_add;
			else
				*token_list_ptr = to_add;
			ft_tokenlst_last(to_add)->next = next;
		}
		prev = current;
		current = next;
	}
}
