/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:55:49 by rtakayam          #+#    #+#             */
/*   Updated: 2025/08/24 12:13:50 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	ft_cmdlst_delone(t_cmd *lst)
// {
// 	if (lst)
// 	{
// 		free(lst->str);
// 		free(lst);
// 	}
// }

// void	ft_cmdlst_clear(t_cmd **lst)
// {
// 	t_cmd	*current;
// 	t_cmd	*nextnode;

// 	if (!lst || !*lst)
// 		return ;
// 	current = *lst;
// 	while (current)
// 	{
// 		nextnode = current->next;
// 		ft_cmdlst_delone(current);
// 		current = nextnode;
// 	}
// 	*lst = NULL;
// }

// t_cmd	*ft_cmdlst_last(t_cmd *lst)
// {
// 	while (lst)
// 	{
// 		if (!lst->next)
// 			return (lst);
// 		lst = lst->next;
// 	}
// 	return (lst);
// }

// void	ft_cmdlst_add_back(t_cmd **lst, t_cmd *new)
// {
// 	t_cmd	*last;

// 	if (*lst)
// 	{
// 		last = ft_cmdlst_last(*lst);
// 		last->next = new;
// 	}
// 	else
// 		*lst = new;
// }

// void	ft_cmdlst_add_front(t_cmd **lst, t_cmd *new)
// {
// 	new->next = *lst;
// 	*lst = new;
// }

// // t_cmd	*ft_cmdlst_new(char *str, t_cmd_type cmd_type,
// // 		t_quote_type quote_type, int is_joined_with_next)
// // {
// // 	t_cmd	*new;

// // 	new = malloc(sizeof(t_cmd));
// // 	if (new == NULL)
// // 	{
// // 		free(str);
// // 		return (NULL);
// // 	}
// // 	new->str = str;
// // 	new->quote_type = quote_type;
// // 	new->cmd_type = cmd_type;
// // 	new->is_joined_with_next = is_joined_with_next;
// // 	new->next = NULL;
// // 	return (new);
// // }