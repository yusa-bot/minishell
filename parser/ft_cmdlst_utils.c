/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinka <rinka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:55:49 by rtakayam          #+#    #+#             */
/*   Updated: 2025/10/27 23:58:33 by rinka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//ここまでredirect_lstここからcmd_lst

t_cmd *ft_cmdlst_init(void)
{
	t_cmd *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->cmd_args = NULL;
	new_cmd->tmp_env = NULL;
	new_cmd->infile = NULL;
	new_cmd->outfile = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd	*ft_cmdlst_new(char **cmd_args, t_env *tmp_env, t_redirect *infile, t_redirect *outfile)
{
	t_cmd	*new;

	new = ft_cmdlst_init();//t_cmd初期化
	if (new == NULL)
		return (NULL);
	new->cmd_args = cmd_args;
	new->tmp_env = tmp_env;
	new->infile = infile;
	new->outfile = outfile;
	return (new);
}

void	ft_cmdlst_delone(t_cmd *lst)
{
	if (lst)
	{
		free_split(lst->cmd_args);
		ft_lst_clear(&(lst->tmp_env));
		if (lst->infile)
			ft_redirectlst_clear(&lst->infile);
		if (lst->outfile)
			ft_redirectlst_clear(&lst->outfile);
		free(lst);
	}
}

void	ft_cmdlst_clear(t_cmd **lst)
{
	t_cmd	*current;
	t_cmd	*nextnode;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		nextnode = current->next;
		ft_cmdlst_delone(current);
		current = nextnode;
	}
	*lst = NULL;
}

t_cmd	*ft_cmdlst_last(t_cmd *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_cmdlst_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (*lst)
	{
		last = ft_cmdlst_last(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

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

//current ;変数展開前後のファイル目を常に保持するように変更
