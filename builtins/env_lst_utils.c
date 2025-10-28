/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:53:18 by ayusa             #+#    #+#             */
/*   Updated: 2025/10/28 11:15:50 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_add_front(t_env **lst, t_env *new)
{
	if (!lst || !new)
	return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lst_delone(t_env *lst)
{
	if (!lst)
	return ;
	if (lst)
	{
		free(lst->key);
		free(lst->value);
		free(lst);
	}
}

void	ft_lst_clear(t_env **lst)
{
	t_env	*current;
	t_env	*nextnode;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		nextnode = current->next;
		ft_lst_delone(current);
		current = nextnode;
	}
	*lst = NULL;
}


t_env   *ft_lst_last(t_env *lst)
{
	if (!lst)
	return (NULL);
	while (lst)
	{
		if (!lst->next)
		return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lst_add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (lst)
	{
		if (*lst)
		{
			last = ft_lst_last(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

t_env *ft_lst_new(char *key, char *value, int is_export)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
	{
		free(key);
		free(value);
		return (NULL);
	}
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->is_export = is_export;
	return (new);
}
