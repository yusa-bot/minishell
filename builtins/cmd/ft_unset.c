/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:31:10 by rinka             #+#    #+#             */
/*   Updated: 2025/10/31 15:26:14 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int unset_key(t_env **env_lst, char *delkey)
{
	t_env *dellst;
	t_env *tmp;

	if (!env_lst || !*env_lst || !delkey)
		return (EXIT_FAILURE);
	tmp = *env_lst;
	if (ft_strcmp(tmp->key, delkey) == 0)
	{
		dellst = tmp;
		*env_lst = tmp->next;
		ft_lst_delone(dellst);
		return (EXIT_SUCCESS);
	}
	while (tmp->next)
	{
		if (ft_strcmp((tmp->next)->key, delkey) == 0)
		{
			dellst = tmp->next;
			tmp->next = (tmp->next)->next;
			ft_lst_delone(dellst);
			break ;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int		ft_unset(t_env **env_lst, char **args)
{
	char *delkey;
	int i;

	if (!env_lst || !*env_lst || !args || !args[0])
		return (EXIT_FAILURE);
	i = 1;
	if (args[i] == NULL)//引数なしの場合そのままリターン
		return (EXIT_SUCCESS);
	while (args[i])
	{
		delkey = args[i];
		if (unset_key(env_lst, delkey) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
