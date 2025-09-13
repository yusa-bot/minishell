/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:55:49 by rtakayam          #+#    #+#             */
/*   Updated: 2025/09/13 21:09:26 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redirectlst_delone(t_redirect *file)
{
	if (!file)
		return ;
	if (file->original_str)
		free(file->original_str);
	if (file->expanded_str)
		free(file->expanded_str);
	free (file);
}

void	ft_redirectlst_clear(t_redirect **lst)
{
	t_redirect	*current;
	t_redirect	*nextnode;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		nextnode = current->next;
		ft_redirectlst_delone(current);
		current = nextnode;
	}
	*lst = NULL;
}

t_redirect *ft_redirectlst_init(void)
{
	t_redirect *new_redirect;

	new_redirect = malloc(sizeof(t_redirect));
	if (new_redirect == NULL)
		return (NULL);
	new_redirect->expanded_str = NULL;
	new_redirect->original_str = NULL;
	new_redirect->token_type = REDIRECT_IN;
	return (new_redirect);
}

t_redirect	*ft_redirectlst_new(char *expanded_str, char *original_str, t_token_type token_type)
{
	t_redirect	*new;

	new = ft_redirectlst_init();//t_cmd初期化
	if (new == NULL)
		return (NULL);
	new->expanded_str = expanded_str;
	new->original_str = original_str;
	new->token_type = token_type;
	return (new);
}

t_redirect	*ft_redirectlst_last(t_redirect *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_redirectlst_add_back(t_redirect **lst, t_redirect *new)
{
	t_redirect	*last;

	if (*lst)
	{
		last = ft_redirectlst_last(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

//ここまでredirect_lstここからcmd_lst

static t_cmd *ft_cmdlst_init(void)
{
	t_cmd *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return (NULL);
		new_cmd->cmd_args = NULL;
		new_cmd->env_vars = NULL;
		new_cmd->infile = NULL;
		new_cmd->outfile = NULL;
		new_cmd->next = NULL;
		return (new_cmd);
}

t_cmd	*ft_cmdlst_new(char **cmd_args, char **env_vars, t_redirect *infile, t_redirect *outfile)
{
	t_cmd	*new;

	new = ft_cmdlst_init();//t_cmd初期化
	if (new == NULL)
		return (NULL);
	new->cmd_args = cmd_args;
	new->env_vars = env_vars;
	new->infile = infile;
	new->outfile = outfile;
	return (new);
}

void	ft_cmdlst_delone(t_cmd *lst)
{
	if (lst)
	{
		ft_free_str_array(lst->cmd_args);
		ft_free_str_array(lst->env_vars);
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