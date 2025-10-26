/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlst_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:55:49 by rtakayam          #+#    #+#             */
/*   Updated: 2025/10/25 20:13:51 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenlst_delone(t_token *lst)
{
	if (lst)
	{
		if (lst->str)
		{
			free(lst->str);
			lst->str = NULL;
		}
		if (lst->original_str)
		{
			free(lst->original_str);
			lst->original_str = NULL;
		}
		free(lst);
		lst = NULL;
	}
}

void	ft_tokenlst_clear(t_token **lst)
{
	t_token	*current;
	t_token	*nextnode;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		nextnode = current->next;
		ft_tokenlst_delone(current);
		current = nextnode;
	}
	*lst = NULL;
}
int	ft_tokenlst_size(t_token *lst)
{
	t_token *tmp;
	int	res;

	tmp = lst;
	res = 0;
	while (tmp)
	{
		res++;
		tmp = tmp->next;
	}
	return (res);
}

t_token	*ft_tokenlst_last(t_token *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_tokenlst_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (*lst)
	{
		last = ft_tokenlst_last(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void	ft_tokenlst_add_front(t_token **lst, t_token *new)
{
	new->next = *lst;
	*lst = new;
}

t_token	*ft_tokenlst_new(char *str, t_token_type token_type,
		t_quote_type quote_type, int is_joined_with_next)
{
	t_token	*new;

	if (!str)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (new == NULL)
	{
		free(str);
		return (NULL);
	}
	new->str = str;
	new->original_str = NULL;
	new->quote_type = quote_type;
	new->token_type = token_type;
	new->is_joined_with_next = is_joined_with_next;
	new->next = NULL;
	return (new);
}
