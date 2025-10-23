/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirectlst_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:15:58 by rinka             #+#    #+#             */
/*   Updated: 2025/10/23 09:10:23 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redirectlst_delone(t_redirect *file)
{
	if (!file)
		return ;
	if (file->original_arg)
		free(file->original_arg);
	if (file->expanded_argi)
		free(file->expanded_argi);
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
	new_redirect->expanded_argi = NULL;
	new_redirect->original_arg = NULL;
	new_redirect->token_type = REDIRECT_IN;
	return (new_redirect);
}

t_redirect	*ft_redirectlst_new(char *expanded_argi, char *original_arg, t_token_type token_type)
{
	t_redirect	*new;

	new = ft_redirectlst_init();//t_cmd初期化
	if (new == NULL)
		return (NULL);
	new->expanded_argi = expanded_argi;
	new->original_arg = original_arg;
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
