/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlst_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:59:06 by rinka             #+#    #+#             */
/*   Updated: 2025/10/09 15:48:56 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token *get_del_min(t_token **lst)
{
	t_token *current_min;
	t_token *tmp = *lst;

	current_min = *lst;
	if (!(*lst)->next)
	{
		*lst = NULL;
		return (current_min);
	}
	while (tmp)
	{
		if (ft_strcmp(current_min->str, tmp->str) > 0)
		{
			current_min = tmp;
		}
		tmp = tmp->next;
	}
	tmp = *lst;
	if (tmp == current_min)
	{
		*lst = (*lst)->next;
		return (current_min);
	}
	while (tmp->next)
	{
		if (tmp->next == current_min)
		{
			tmp->next = tmp->next->next;
			break ;
		}
		tmp = tmp->next;
	}
	return (current_min);
}

static void add_back(t_token **res, t_token *current_min)
{
	t_token *tmp = *res;

	if (!tmp)
	{
		*res = current_min;
		(*res)->next = NULL;
		return ;
	}
	while (tmp->next)
	{
		tmp = (tmp)->next;
	}	
	tmp->next = current_min;
	tmp = tmp->next;
	tmp->next = NULL;
}

t_token	*ft_tokenlst_sort(t_token* lst)
{
	t_token *res = NULL;
	t_token *tmp = lst;
	t_token *current_min;

	while (tmp)
	{
		current_min = get_del_min(&tmp);
		add_back(&res, current_min);
	}
	return (res);
}
