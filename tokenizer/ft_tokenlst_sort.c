/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenlst_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:59:06 by rinka             #+#    #+#             */
/*   Updated: 2025/10/31 18:43:58 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *get_min(t_token **lst)
{
	t_token *res;
	t_token *tmp;

	tmp = *lst;
	res = *lst;
	while (tmp)
	{
		if (ft_strcmp(res->str, tmp->str) > 0)
			res = tmp;
		tmp = tmp->next;
	}
	return (res);
}

static t_token *get_del_min(t_token **lst)
{
	t_token *min;
	t_token *tmp;
	
	tmp = *lst;
	if (!(*lst)->next)
	{
		*lst = NULL;
		return (tmp);
	}
	min = get_min(lst);
	if (tmp == min)
	{
		*lst = (*lst)->next;
		return (min);
	}
	while (tmp->next)
	{
		if (tmp->next == min)
		{
			tmp->next = tmp->next->next;
			break ;
		}
		tmp = tmp->next;
	}
	return (min);
}

static void add_back(t_token **res, t_token *min)
{
	t_token *tmp = *res;

	if (!tmp)
	{
		*res = min;
		(*res)->next = NULL;
		return ;
	}
	while (tmp->next)
	{
		tmp = (tmp)->next;
	}	
	tmp->next = min;
	tmp = tmp->next;
	tmp->next = NULL;
}

t_token	*ft_tokenlst_sort(t_token* lst)
{
	t_token *res = NULL;
	t_token *tmp = lst;
	t_token *min;

	while (tmp)
	{
		min = get_del_min(&tmp);
		add_back(&res, min);
	}
	return (res);
}
