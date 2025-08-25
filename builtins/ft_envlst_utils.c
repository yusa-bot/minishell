/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envlst__utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:30:45 by rinka             #+#    #+#             */
/*   Updated: 2025/08/11 14:54:17 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envlst_delone(t_env *lst)
{
	if (lst)
	{
		free(lst->key);
		free(lst->value);
		free(lst);
	}
}

void	ft_envlst_clear(t_env **lst)
{
	t_env	*current;
	t_env	*nextnode;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		nextnode = current->next;
		ft_envlst_delone(current);
		current = nextnode;
	}
	*lst = NULL;
}

t_env *ft_envlst_last(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_envlst_add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_envlst_last(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

void	ft_envlst_add_front(t_env **lst, t_env *new)
{
	new->next = *lst;
	*lst = new;
}

t_env *ft_envlst_new(char *key, char *value, int is_export)
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

// t_env ft_envlst_get(t_env *lst, char *key)
// {
// 	while(lst)
// 	{
// 		if (ft_strcmp(lst->key, key) == 0)
// 			return (lst)
// 	}
// }