/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:14:33 by ayusa             #+#    #+#             */
/*   Updated: 2025/09/14 16:33:25 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

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
