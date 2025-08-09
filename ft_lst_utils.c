/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:30:45 by rinka             #+#    #+#             */
/*   Updated: 2025/08/10 00:33:04 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

void	ft_lstdelone(t_env *lst)
{
	if (lst)
	{
		free(lst->key);
		free(lst->value);
		free(lst);
	}
}

void	ft_lstclear(t_env **lst)//使ってない
{
	t_env	*tmp;

	if (!lst || !*lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst);
		*lst = tmp;
	}
}

t_env *ft_lstlast(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

t_env *ft_lstnew(char *key, char *value, int is_export)
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

// t_env ft_lstget(t_env *lst, char *key)
// {
// 	while(lst)
// 	{
// 		if (ft_strcmp(lst->key, key) == 0)
// 			return (lst)
// 	}
// }