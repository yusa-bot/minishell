/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirectlst_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:15:58 by rinka             #+#    #+#             */
/*   Updated: 2025/10/09 15:19:44 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redirectlst_delone(t_redirect *file)
{
	if (!file)
		return ;
	if (file->original_filename)
		free(file->original_filename);
	if (file->expanded_filename)
		free(file->expanded_filename);
	free (file);
}

void	ft_redirectlst_clear(t_redirect **lst)
{
	t_redirect	*current;
	t_redirect	*nextnode;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		nextnode = current->next;
		ft_redirectlst_delone(current);
		current = nextnode;
	}
	*lst = NULL;
}

t_redirect *ft_redirectlst_init(void)
{
	t_redirect *new_redirect;

	new_redirect = malloc(sizeof(t_redirect));
	if (new_redirect == NULL)
		return (NULL);
	new_redirect->expanded_filename = NULL;
	new_redirect->original_filename = NULL;
	new_redirect->token_type = REDIRECT_IN;
	return (new_redirect);
}

t_redirect	*ft_redirectlst_new(char *expanded_filename, char *original_filename, t_token_type token_type)
{
	t_redirect	*new;

	new = ft_redirectlst_init();//t_cmd初期化
	if (new == NULL)
		return (NULL);
	new->expanded_filename = expanded_filename;
	new->original_filename = original_filename;
	new->token_type = token_type;
	return (new);
}

t_redirect	*ft_redirectlst_last(t_redirect *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_redirectlst_add_back(t_redirect **lst, t_redirect *new)
{
	t_redirect	*last;

	if (*lst)
	{
		last = ft_redirectlst_last(*lst);
		last->next = new;
	}
	else
		*lst = new;
}
