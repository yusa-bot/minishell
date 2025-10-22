/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 00:31:10 by rinka             #+#    #+#             */
/*   Updated: 2025/10/23 08:38:16 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_unset(t_env **env_lst, char *delkey)
{
	t_env *dellst;
	t_env *tmp;

	if (!env_lst || !*env_lst || !delkey)
		return (EXIT_FAILURE);
	tmp = *env_lst;
	if (ft_strcmp(tmp->key, delkey) == 0)
	{
		dellst = tmp;
		*env_lst = tmp->next;  // リストの先頭を更新
		ft_lst_delone(dellst);
		//tmp = tmp->next;
		return (EXIT_SUCCESS);
	}
	while (tmp->next)
	{
		if (ft_strcmp((tmp->next)->key, delkey) == 0)
		{
			dellst = tmp->next;
			tmp->next = (tmp->next)->next;
			ft_lst_delone(dellst);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_FAILURE);
}
